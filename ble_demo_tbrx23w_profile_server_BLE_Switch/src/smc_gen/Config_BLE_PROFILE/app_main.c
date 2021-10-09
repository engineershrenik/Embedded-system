/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2019-2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/******************************************************************************
* File Name    : app_main.c
* Device(s)    : RX23W
* Tool-Chain   : e2Studio, Renesas RX v2.08
* Description  : This is a application file for peripheral role.
*******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include <string.h>
#include "r_ble_rx23w_if.h"
#include "abs/r_ble_abs_api.h"
#include "timer/r_ble_timer.h"
#include "gatt_db.h"
#include "profile_cmn/r_ble_servs_if.h"
#include "profile_cmn/r_ble_servc_if.h"
#include "r_ble_lss.h"

#if (BSP_CFG_RTOS_USED == 1)
#include "rtos/r_ble_rtos.h"
#include "FreeRTOS.h"
#include "task.h"
#include "../frtos_skeleton/task_function.h"
#endif

#define BLE_LOG_TAG "app_main"
#include "logger/r_ble_logger.h"

/******************************************************************************
 User file includes
*******************************************************************************/
/* Start user code for file includes. Do not edit comment generated here */
#include "board/r_ble_board.h"
#include "cmd/r_ble_cmd_abs.h"
#include "cmd/r_ble_cmd_vs.h"
#include "cmd/r_ble_cmd_sys.h"
/* End user code. Do not edit comment generated here */

/******************************************************************************
 User macro definitions
*******************************************************************************/
/* Queue for Prepare Write Operation. Change if needed. */
#define BLE_GATTS_QUEUE_ELEMENTS_SIZE       (14)
#define BLE_GATTS_QUEUE_BUFFER_LEN          (245)
#define BLE_GATTS_QUEUE_NUM                 (1)

/* Start user code for macro definitions. Do not edit comment generated here */
/******************************************************************************
 Application Config
 ******************************************************************************/
#define APP_CFG_NOTIF_GUARD_EN      (0)//(1)     /* Notification guard [0:Disable/1:Enable] */
#define APP_CFG_NOTIF_GUARD_TIME    (200)   /* Notification guard time [unit: msec] */

/* End user code. Do not edit comment generated here */

/******************************************************************************
 Generated function prototype declarations
*******************************************************************************/
/* Internal functions */
static void gap_cb(uint16_t type, ble_status_t result, st_ble_evt_data_t *p_data);
static void gatts_cb(uint16_t type, ble_status_t result, st_ble_gatts_evt_data_t *p_data);
static void gattc_cb(uint16_t type, ble_status_t result, st_ble_gattc_evt_data_t *p_data);
static void vs_cb(uint16_t type, ble_status_t result, st_ble_vs_evt_data_t *p_data);
static ble_status_t ble_init(void);
void app_main(void);

/******************************************************************************
 User function prototype declarations
*******************************************************************************/
/* Start user code for function prototype declarations. Do not edit comment generated here */
static void ble_host_stack_init(void);
static void timer_cb(uint32_t timer_hdl);
static void sw_cb(void);

#if (APP_CFG_NOTIF_GUARD_EN != 0)
static void notif_timer_cb(uint32_t timer_hdl);
#endif /* (APP_CFG_NOTIF_GUARD_EN != 0) */

/* End user code. Do not edit comment generated here */

/******************************************************************************
 Generated global variables
*******************************************************************************/
/* Advertising Data */
static uint8_t gs_adv_data[] =
{
    /* Flags */
    0x02, /**< Data Size */
    0x01, /**< Data Type */
    ( 0x06 ), /**< Data Value */
};

/* Advertising parameters */
static st_ble_abs_legacy_adv_param_t gs_adv_param =
{
    .slow_adv_intv      = 0x00000640, ///< Slow advertising interval. 1,000.0(ms)
    .slow_period        = 0x0000,      ///< Slow advertising period. 0(ms)
    .p_adv_data         = gs_adv_data,             ///< Advertising data. If p_advertising_data is specified as NULL, advertising data is not set.
    .adv_data_length    = ARRAY_SIZE(gs_adv_data), ///< Advertising data length (in bytes).
    .filter             = BLE_ABS_ADV_ALLOW_CONN_ANY, ///< Advertising Filter Policy.
    .adv_ch_map         = ( BLE_GAP_ADV_CH_37 | BLE_GAP_ADV_CH_38 | BLE_GAP_ADV_CH_39 ), ///< Channel Map.
#if (BLE_VERSION_MAJOR > 1) || ((BLE_VERSION_MAJOR == 1) && (BLE_VERSION_MINOR >= 10))
    .o_addr_type        = BLE_GAP_ADDR_RAND, ///< Own Bluetooth address type.
    .o_addr             = { 0 },
#else
    .o_addr_type        = BLE_GAP_ADDR_PUBLIC,
#endif
};

/* GATT server callback parameters */
static st_ble_abs_gatts_cb_param_t gs_abs_gatts_cb_param[] =
{
    {
        .cb         = gatts_cb,
        .priority   = 1,
    },
    {
        .cb         = NULL,
    }
};

/* GATT server initialization parameters */
static st_ble_abs_gatts_init_param_t gs_abs_gatts_init_param =
{
    .p_cb_param = gs_abs_gatts_cb_param,
    .cb_num     = BLE_GATTS_MAX_CB,
};

/* GATT client callback parameters */
static st_ble_abs_gattc_cb_param_t gs_abs_gattc_cb_param[] =
{
    {
        .cb         = gattc_cb,
        .priority   = 1,
    },
    {
        .cb         = NULL,
    }
};

/* GATT client initialization parameters */
static st_ble_abs_gattc_init_param_t gs_abs_gattc_init_param =
{
    .p_cb_param = gs_abs_gattc_cb_param,
    .cb_num     = BLE_GATTC_MAX_CB,
};

/* Pairing parameters */
static st_ble_abs_pairing_param_t gs_abs_pairing_param =
{
    .iocap          = BLE_GAP_IOCAP_NOINPUT_NOOUTPUT,
    .mitm           = BLE_GAP_SEC_MITM_BEST_EFFORT,
    .sec_conn_only  = BLE_GAP_SC_BEST_EFFORT,
    .loc_key_dist   = BLE_GAP_KEY_DIST_ENCKEY,
    .rem_key_dist   = 0,
    .max_key_size   = 16,
};

/* Host stack initialization parameters */
static st_ble_abs_init_param_t gs_abs_init_param =
{
    .gap_cb          = gap_cb,
    .p_gatts_cbs     = &gs_abs_gatts_init_param,
    .p_gattc_cbs     = &gs_abs_gattc_init_param,
    .vs_cb           = vs_cb,
    .p_pairing_param = &gs_abs_pairing_param,
};

/* GATT server Prepare Write Queue parameters */
static st_ble_gatt_queue_elm_t  gs_queue_elms[BLE_GATTS_QUEUE_ELEMENTS_SIZE];
static uint8_t gs_buffer[BLE_GATTS_QUEUE_BUFFER_LEN];
static st_ble_gatt_pre_queue_t gs_queue[BLE_GATTS_QUEUE_NUM] = {
    {
        .p_buf_start = gs_buffer,
        .buffer_len  = BLE_GATTS_QUEUE_BUFFER_LEN,
        .p_queue     = gs_queue_elms,
        .queue_size  = BLE_GATTS_QUEUE_ELEMENTS_SIZE,
    }
};

/* Connection handle */
uint16_t g_conn_hdl;

/******************************************************************************
 User global variables
*******************************************************************************/
/* Start user code for global variables. Do not edit comment generated here */
/* CommandLine parameters */
static const st_ble_cli_cmd_t * const gsp_cmds[] =
{
    &g_abs_cmd,
    &g_vs_cmd,
    &g_sys_cmd,
    &g_ble_cmd
};

/* timer handle */
static uint32_t gs_timer_hdl;
static uint8_t gs_get_addr_status;

#if (APP_CFG_NOTIF_GUARD_EN != 0)
static uint32_t gs_notif_timer_hdl;
static volatile uint32_t gs_notif_status;
#endif /* (APP_CFG_NOTIF_GUARD_EN != 0) */
/* End user code. Do not edit comment generated here */

/******************************************************************************
 Generated function definitions
*******************************************************************************/
/******************************************************************************
 * Function Name: gap_cb
 * Description  : Callback function for GAP API.
 * Arguments    : uint16_t type -
 *                  Event type of GAP API.
 *              : ble_status_t result -
 *                  Event result of GAP API.
 *              : st_ble_vs_evt_data_t *p_data - 
 *                  Event parameters of GAP API.
 * Return Value : none
 ******************************************************************************/
static void gap_cb(uint16_t type, ble_status_t result, st_ble_evt_data_t *p_data)
{
/* Hint: Input common process of callback function such as variable definitions */
/* Start user code for GAP callback function common process. Do not edit comment generated here */
    R_BLE_CMD_AbsGapCb(type, result, p_data);
/* End user code. Do not edit comment generated here */

    switch(type)
    {
        case BLE_GAP_EVENT_STACK_ON:
        {
#if (BLE_VERSION_MAJOR > 1) || ((BLE_VERSION_MAJOR == 1) && (BLE_VERSION_MINOR >= 10))
            /* Get BD address for Advertising */
            R_BLE_VS_GetBdAddr(BLE_VS_ADDR_AREA_REG, BLE_GAP_ADDR_RAND);
#else
            /* Start Advertising when BLE protocol stack is ready */
            R_BLE_ABS_StartLegacyAdv(&gs_adv_param);
#endif
        } break;

        case BLE_GAP_EVENT_CONN_IND:
        {
            if (BLE_SUCCESS == result)
            {
                /* Store connection handle */
                st_ble_gap_conn_evt_t *p_gap_conn_evt_param = (st_ble_gap_conn_evt_t *)p_data->p_param;
                g_conn_hdl = p_gap_conn_evt_param->conn_hdl;
            }
            else
            {
                /* Restart advertising when connection failed */
                R_BLE_ABS_StartLegacyAdv(&gs_adv_param);
            }
        } break;

        case BLE_GAP_EVENT_DISCONN_IND:
        {
            /* Restart advertising when disconnected */
            g_conn_hdl = BLE_GAP_INVALID_CONN_HDL;
            R_BLE_ABS_StartLegacyAdv(&gs_adv_param);
        } break;

        case BLE_GAP_EVENT_CONN_PARAM_UPD_REQ:
        {
            /* Send connection update response with value received on connection update request */
            st_ble_gap_conn_upd_req_evt_t *p_conn_upd_req_evt_param = (st_ble_gap_conn_upd_req_evt_t *)p_data->p_param;

            st_ble_gap_conn_param_t conn_updt_param = {
                .conn_intv_min = p_conn_upd_req_evt_param->conn_intv_min,
                .conn_intv_max = p_conn_upd_req_evt_param->conn_intv_max,
                .conn_latency  = p_conn_upd_req_evt_param->conn_latency,
                .sup_to        = p_conn_upd_req_evt_param->sup_to,
                .min_ce_length = 0xFFFF,
                .max_ce_length = 0xFFFF,
            };

            R_BLE_GAP_UpdConn(p_conn_upd_req_evt_param->conn_hdl,
                              BLE_GAP_CONN_UPD_MODE_RSP,
                              BLE_GAP_CONN_UPD_ACCEPT,
                              &conn_updt_param);
        } break;

/* Hint: Add cases of GAP event macros defined as BLE_GAP_XXX */
/* Start user code for GAP callback function event process. Do not edit comment generated here */
        case BLE_GAP_EVENT_DATA_LEN_CHG:
        case BLE_GAP_EVENT_PHY_UPD:
        case BLE_GAP_EVENT_CONN_PARAM_UPD_COMP:
        {
            /* Do nothing. */
        } break;

        default:
            break;
/* End user code. Do not edit comment generated here */
    }

/* Start user code for GAP callback function closing process. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
}

/******************************************************************************
 * Function Name: gatts_cb
 * Description  : Callback function for GATT Server API.
 * Arguments    : uint16_t type -
 *                  Event type of GATT Server API.
 *              : ble_status_t result -
 *                  Event result of GATT Server API.
 *              : st_ble_gatts_evt_data_t *p_data - 
 *                  Event parameters of GATT Server API.
 * Return Value : none
 ******************************************************************************/
static void gatts_cb(uint16_t type, ble_status_t result, st_ble_gatts_evt_data_t *p_data)
{
/* Hint: Input common process of callback function such as variable definitions */
/* Start user code for GATT Server callback function common process. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

    R_BLE_SERVS_GattsCb(type, result, p_data);
    switch(type)
    {
/* Hint: Add cases of GATT Server event macros defined as BLE_GATTS_XXX */
/* Start user code for GATT Server callback function event process. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
    }

/* Start user code for GATT Server callback function closing process. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
}

/******************************************************************************
 * Function Name: gattc_cb
 * Description  : Callback function for GATT Client API.
 * Arguments    : uint16_t type -
 *                  Event type of GATT Client API.
 *              : ble_status_t result -
 *                  Event result of GATT Client API.
 *              : st_ble_gattc_evt_data_t *p_data - 
 *                  Event parameters of GATT Client API.
 * Return Value : none
 ******************************************************************************/
static void gattc_cb(uint16_t type, ble_status_t result, st_ble_gattc_evt_data_t *p_data)
{
/* Hint: Input common process of callback function such as variable definitions */
/* Start user code for GATT Client callback function common process. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

    R_BLE_SERVC_GattcCb(type, result, p_data);
    switch(type)
    {

/* Hint: Add cases of GATT Client event macros defined as BLE_GATTC_XXX */
/* Start user code for GATT Client callback function event process. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
    }

/* Start user code for GATT Client callback function closing process. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
}

/******************************************************************************
 * Function Name: vs_cb
 * Description  : Callback function for Vendor Specific API.
 * Arguments    : uint16_t type -
 *                  Event type of Vendor Specific API.
 *              : ble_status_t result -
 *                  Event result of Vendor Specific API.
 *              : st_ble_vs_evt_data_t *p_data - 
 *                  Event parameters of Vendor Specific API.
 * Return Value : none
 ******************************************************************************/
static void vs_cb(uint16_t type, ble_status_t result, st_ble_vs_evt_data_t *p_data)
{
/* Hint: Input common process of callback function such as variable definitions */
/* Start user code for vender specific callback function common process. Do not edit comment generated here */
    R_BLE_CMD_VsCb(type, result, p_data);
/* End user code. Do not edit comment generated here */

    R_BLE_SERVS_VsCb(type, result, p_data);
    switch(type)
    {
#if (BLE_VERSION_MAJOR > 1) || ((BLE_VERSION_MAJOR == 1) && (BLE_VERSION_MINOR >= 10))
        case BLE_VS_EVENT_GET_ADDR_COMP:
        {
            /* Start advertising when BD address is ready */
            st_ble_vs_get_bd_addr_comp_evt_t * p_get_addr = (st_ble_vs_get_bd_addr_comp_evt_t *)p_data->p_param;
            memcpy(gs_adv_param.o_addr, p_get_addr->addr.addr, BLE_BD_ADDR_LEN);
            R_BLE_ABS_StartLegacyAdv(&gs_adv_param);
        } break;
#endif

/* Hint: Add cases of vender specific event macros defined as BLE_VS_XXX */
/* Start user code for vender specific callback function event process. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
    }

/* Start user code for vender specific callback function closing process. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
}

/******************************************************************************
 * Function Name: lss_cb
 * Description  : Callback function for LED Switch Service server feature.
 * Arguments    : uint16_t type -
 *                  Event type of LED Switch Service server feature.
 *              : ble_status_t result -
 *                  Event result of LED Switch Service server feature.
 *              : st_ble_servs_evt_data_t *p_data - 
 *                  Event parameters of LED Switch Service server feature.
 * Return Value : none
 ******************************************************************************/
static void lss_cb(uint16_t type, ble_status_t result, st_ble_servs_evt_data_t *p_data)
{
/* Hint: Input common process of callback function such as variable definitions */
/* Start user code for LED Switch Service Server callback function common process. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

    switch(type)
    {
/* Hint: Add cases of LED Switch Service server events defined in e_ble_lss_event_t */
/* Start user code for LED Switch Service Server callback function event process. Do not edit comment generated here */
        case BLE_LSS_EVENT_BLINK_RATE_WRITE_REQ:
        {
            if( BLE_SUCCESS != result )
            {
                R_BLE_GATTS_SendErrRsp(BLE_ERR_GATT_INVALID_ATTRIBUTE_LEN);
            }
        } break;

        case BLE_LSS_EVENT_BLINK_RATE_WRITE_COMP:
        {
            uint8_t rate = *(uint8_t *)p_data->p_param;
            if (0 == rate)
            {
                R_BLE_TIMER_Stop(gs_timer_hdl);
                R_BLE_BOARD_SetLEDState(BLE_BOARD_LED1, false);
            }
            else
            {
                R_BLE_TIMER_UpdateTimeout(gs_timer_hdl, rate * 100);
            }
        } break;

        default:
            break;
/* End user code. Do not edit comment generated here */
    }

/* Start user code for LED Switch Service Server callback function closing process. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
}
/******************************************************************************
 * Function Name: ble_init
 * Description  : Initialize host stack and profiles.
 * Arguments    : none
 * Return Value : BLE_SUCCESS - SUCCESS
 *                BLE_ERR_INVALID_OPERATION -
 *                    Failed to initialize host stack or profiles.
 ******************************************************************************/
static ble_status_t ble_init(void)
{
    ble_status_t status;

    /* Initialize the Low Power Control function */
    R_BLE_LPC_Init();

    /* Initialize Timer Library */
    R_BLE_TIMER_Init();

    /* Initialize host stack */
    status = R_BLE_ABS_Init(&gs_abs_init_param);
    if (BLE_SUCCESS != status)
    {
        return BLE_ERR_INVALID_OPERATION;
    }

    /* Initialize GATT Database */
    status = R_BLE_GATTS_SetDbInst(&g_gatt_db_table);
    if (BLE_SUCCESS != status)
    {
        return BLE_ERR_INVALID_OPERATION;
    }

    /* Initialize GATT server */
    status = R_BLE_SERVS_Init();
    if (BLE_SUCCESS != status)
    {
        return BLE_ERR_INVALID_OPERATION;
    }

    /* Initialize GATT client */
    status = R_BLE_SERVC_Init();
    if (BLE_SUCCESS != status)
    {
        return BLE_ERR_INVALID_OPERATION;
    }

    /* Set Prepare Write Queue */
    R_BLE_GATTS_SetPrepareQueue(gs_queue, BLE_GATTS_QUEUE_NUM);

    /* Initialize LED Switch Service server API */
    status = R_BLE_LSS_Init(lss_cb);
    if (BLE_SUCCESS != status)
    {
        return BLE_ERR_INVALID_OPERATION;
    }

    return status;
}

/******************************************************************************
 * Function Name: app_main
 * Description  : Application main function with main loop
 * Arguments    : none
 * Return Value : none
 ******************************************************************************/
void app_main(void)
{
    /* Initialize BLE */
    R_BLE_Open();

    /* Initialize host stack and profiles */
    ble_init();

/* Hint: Input process that should be done before main loop such as calling initial function or variable definitions */
/* Start user code for process before main loop. Do not edit comment generated here */
    /* Configure the board */
    R_BLE_BOARD_Init();
    R_BLE_BOARD_RegisterSwitchCb(BLE_BOARD_SW2, sw_cb);

    /* Configure CommandLine */
    R_BLE_CLI_Init();
    R_BLE_CLI_RegisterCmds(gsp_cmds, ARRAY_SIZE(gsp_cmds));
    R_BLE_CMD_SetResetCb(ble_host_stack_init);
/* End user code. Do not edit comment generated here */

    /* main loop */
    while (1)
    {
/* Hint: Input process that should be done before BLE_Execute in main loop */
/* Start user code for process before BLE_Execute. Do not edit comment generated here */
        /* Process Command Line */
        R_BLE_CLI_Process();
/* End user code. Do not edit comment generated here */

        /* Process BLE Event */
        R_BLE_Execute();

#if (BSP_CFG_RTOS_USED == 0)
        /* Enter the MCU Lower Power Mode */
        R_BLE_LPC_EnterLowPowerMode();
#elif (BSP_CFG_RTOS_USED == 1)
        if(0 != R_BLE_IsTaskFree()) 
        {
        	ulTaskNotifyTake(pdFALSE, portMAX_DELAY);
        }
#endif

/* Hint: Input process that should be done during main loop such as calling processing functions */
/* Start user code for process during main loop. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
    }

/* Hint: Input process that should be done after main loop such as calling closing functions */
/* Start user code for process after main loop. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

    /* Terminate BLE */
    R_BLE_Close();
}

/******************************************************************************
 User function definitions
*******************************************************************************/
/* Start user code for function definitions. Do not edit comment generated here */

/******************************************************************************
 * Function Name: ble_host_stack_init
 * Description  : Reset Host Stack.
 * Arguments    : none
 * Return Value : none
 ******************************************************************************/
static void ble_host_stack_init(void)
{
    ble_init();
}

/******************************************************************************
 * Function Name: sw_cb
 * Description  : Callback function for board switch.
 * Arguments    : none
 * Return Value : none
 ******************************************************************************/
static void sw_cb(void)
{
#if (APP_CFG_NOTIF_GUARD_EN != 0)
    if( BLE_GAP_INVALID_CONN_HDL == g_conn_hdl )
    {
        return;
    }
    if( 0 == gs_notif_status )
    {
        gs_notif_status = 1;

        uint8_t state = 1;
        (void)R_BLE_LSS_NotifySwitchState(g_conn_hdl, &state);

        (void)R_BLE_TIMER_Start(gs_notif_timer_hdl);
    }
#else /* (APP_CFG_NOTIF_GUARD_EN != 0) */
    uint8_t state = 1;
    R_BLE_LSS_NotifySwitchState(g_conn_hdl, &state);
#endif /* (APP_CFG_NOTIF_GUARD_EN != 0) */
}

/******************************************************************************
 * Function Name: timer_cb
 * Description  : Callback function for timer for LED blink.
 * Arguments    : uint32_t timer_hdl -
 *                  Timer handle identifying a expired timer.
 * Return Value : none
 ******************************************************************************/
static void timer_cb(uint32_t timer_hdl)
{
    R_BLE_BOARD_ToggleLEDState(BLE_BOARD_LED1);
}

/******************************************************************************
 * Function Name: notif_timer_cb
 * Description  : Callback function for timer for chattering prevention.
 * Arguments    : uint32_t timer_hdl -
 *                  Timer handle identifying a expired timer.
 * Return Value : none
 ******************************************************************************/
#if (APP_CFG_NOTIF_GUARD_EN != 0)
static void notif_timer_cb(uint32_t timer_hdl)
{
    if( timer_hdl != gs_notif_timer_hdl )
    {
        return;
    }
    if( 0 != gs_notif_status )
    {
        gs_notif_status = 0;
    }
}
#endif /* (APP_CFG_NOTIF_GUARD_EN != 0) */

/* End user code. Do not edit comment generated here */
