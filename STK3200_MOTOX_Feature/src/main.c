/**************************************************************************//**
 * @file main.c
 * @brief Clock example for EFM32ZG-STK3200
 * @version 3.20.5
 *
 * This example shows how to optimize your code in order to drive
 * a graphical display in an energy friendly way.
 *
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silabs License Agreement. See the file
 * "Silabs_License_Agreement.txt" for details. Before using this software for
 * any purpose, you must agree to the terms of that agreement.
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <time.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_pcnt.h"
#include "em_prs.h"
#include "display.h"
#include "glib.h"
#include "em_adc.h"


#include "i2cdrv.h"
//#include "si7013.h"
#include "si114x_algorithm.h"
#include "si114x_functions.h"


/* Frequency of RTC (COMP0) pulses on PRS channel 2 
   = frequency of LCD polarity inversion. */
#define RTC_PULSE_FREQUENCY    (64)



#define PS_HOVER_THRESHOLD    295 //SHRENIK
/** I2C device address for Si1147 on weather station board. */
#define SI1147_ADDR    0xc0 //SHRENIK
#define SI1147_DEVICE_ID      0x47 //SHRENIK


/* Clock mode */
typedef enum
{
  CLOCK_MODE_ANALOG,
  CLOCK_MODE_DIGITAL
} ClockMode_t;
volatile ClockMode_t clockMode = CLOCK_MODE_ANALOG;

/* The current time reference. Number of seconds since midnight
 * January 1, 1970.  */
static volatile time_t curTime = 0;

/* PCNT interrupt counter */
static volatile int pcntIrqCount = 0;

/* Flag to check when we should redraw a frame */
static volatile bool updateDisplay = true;
static volatile bool timeIsFastForwarding = false;

/* Global glib context */
GLIB_Context_t gc;

/* Analog clock prototypes */
void analogClockInitGraphics(void);
void analogClockUpdate(struct tm *t, bool forceRedraw);
static void adcInit( void );	//Shrenik

#if 0
static si114x_i2c_t si114x_i2c;
static si114x_i2c_t *si114x_handle = &si114x_i2c;
/**************************************************************************//**
 * @brief
  *  Detects whether Si1147 is on the i2c bus
 * @param[in] i2c
 *   The I2C peripheral to use (not used).
 * @param[in] addr
 *   The I2C address of the sensor.
 * @return
 *   Returns 1 on success. Otherwise returns 0.
 *****************************************************************************/
int Si1147_Detect_Device(I2C_TypeDef *i2c, uint8_t addr)
{
  uint8_t data;
  si114x_handle->addr = addr;
  si114x_handle->i2c  = i2c;
  data                = Si114xReadFromRegister(si114x_handle, 0);

  if (data == SI1147_DEVICE_ID)
  {
    return 1;
  }
  return 0;
}

/**************************************************************************//**
 * @brief
  *  Get the enable status of the Si1147 interrupt pin
 * @param[in] i2c
 *   The I2C peripheral to use (not used).
 * @param[in] addr
 *   The I2C address of the sensor.
 * @param[out] enable
 *   Will be set to 1 if the interrupt output pin is enabled
 *   or set to 0 if disabled.
 * @return
 *   Returns 0.
 *****************************************************************************/
int Si1147_GetInterruptOutputEnable(I2C_TypeDef *i2c, uint8_t addr, int *enable)
{
  int retval = 0;
  si114x_handle->addr = addr;
  si114x_handle->i2c  = i2c;
  *enable             = Si114xReadFromRegister(si114x_handle, REG_INT_CFG);
  return retval;
}


/**************************************************************************//**
 * @brief
  *  Reads the UV measurement data and checks for object in proximity to the
  *  Si1147.
 * @param[in] i2c
 *   The I2C peripheral to use (not used).
 * @param[in] addr
 *   The I2C address of the sensor.
 * @param[out] uvIndex
 *   The UV index read from the sensor
 * @param[out] objectDetect
 *   Returns true if an object is detected in front of the sensor, otherwise
 *   false.
 * @return
 *   Returns 0.
 *****************************************************************************/

int Si1147_MeasureUVAndObjectPresent(I2C_TypeDef *i2c, uint8_t addr, uint16_t *uvIndex, int *objectDetect)
{
  uint16_t data;
  int      retval = 0;
  int      gestureMode;
  *objectDetect       = 0;
  si114x_handle->addr = addr;
  si114x_handle->i2c  = i2c;
  Si1147_GetInterruptOutputEnable(i2c,addr,&gestureMode);
  if ( !gestureMode ) /* Force only if not already running swipe detection. */
  {
    Si114xPsAlsForce(si114x_handle);
    while ((Si114xReadFromRegister(si114x_handle, REG_IRQ_STATUS) & 1) == 0)
    ;                                                           /*wait for measurement data */
  }
  data  = Si114xReadFromRegister(si114x_handle, REG_AUX_DATA0); /*read sample data from si114x */
  data |= Si114xReadFromRegister(si114x_handle, REG_AUX_DATA1) << 8;
  /*round to nearest*/
  *uvIndex  = data + 50;
  *uvIndex /= 100;

  if ( !gestureMode ) /* Check for object only if not already running swipe detection. */
  {
    data  = Si114xReadFromRegister(si114x_handle, REG_PS1_DATA0); /*read sample data from si114x */
    data |= Si114xReadFromRegister(si114x_handle, REG_PS1_DATA1) << 8;
    if (data > PS_HOVER_THRESHOLD)
    {
      *objectDetect = 1;
    }
  }
  /*clear irq*/
  Si114xWriteToRegister(si114x_handle, REG_IRQ_STATUS, 0xff);

  return retval;
}
#endif

/**************************************************************************//**
 * @brief ADC Initialization
 *****************************************************************************/
static void adcInit( void ) {

   ADC_Init_TypeDef       init       = ADC_INIT_DEFAULT;
   ADC_InitSingle_TypeDef initSingle = ADC_INITSINGLE_DEFAULT;

   /* Enable ADC clock */
   CMU_ClockEnable( cmuClock_ADC0, true );

   /* Initiate ADC peripheral */
   ADC_Init(ADC0, &init);

   /* Setup single conversions for internal VDD/3 */
   initSingle.acqTime = adcAcqTime16;
   initSingle.input   = adcSingleInpVDDDiv3;
   ADC_InitSingle( ADC0, &initSingle );

   /* Manually set some calibration values */
   ADC0->CAL = (0x7C << _ADC_CAL_SINGLEOFFSET_SHIFT) | (0x1F << _ADC_CAL_SINGLEGAIN_SHIFT);

   /* Enable interrupt on completed conversion */
   ADC_IntEnable(ADC0, ADC_IEN_SINGLE);
   NVIC_ClearPendingIRQ( ADC0_IRQn );
   NVIC_EnableIRQ( ADC0_IRQn );
}


/**************************************************************************//**
 * @brief Setup GPIO interrupt for pushbuttons.
 *****************************************************************************/
static void gpioSetup(void)
{
  /* Enable GPIO clock */
  CMU_ClockEnable(cmuClock_GPIO, true);

  /* Configure PC8 as input and enable interrupt  */
  GPIO_PinModeSet(gpioPortC, 8, gpioModeInputPull, 1);
  GPIO_IntConfig(gpioPortC, 8, false, true, true);

  NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
  NVIC_EnableIRQ(GPIO_EVEN_IRQn);

  /* Configure PC9 as input and enable interrupt */
  GPIO_PinModeSet(gpioPortC, 9, gpioModeInputPull, 1);
  GPIO_IntConfig(gpioPortC, 9, false, true, true);

  NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
  NVIC_EnableIRQ(GPIO_ODD_IRQn);

  /* Configure PD4 as pushpull. (5v enable signal) */
    GPIO_PinModeSet(gpioPortD, 4, gpioModePushPull, 0);
    GPIO_PinOutClear(gpioPortD, 4);

    /* Configure PD5 as input and enable interrupt - proximity interrupt. */
    /* Interrupt is active low */
    GPIO_PinModeSet(gpioPortD, 5, gpioModeInputPull, 1);
    GPIO_IntConfig(gpioPortD, 5, false, true, true);

    /*Enable 5V supply to add-on board. */
    GPIO_PinOutSet(gpioPortD, 4);
}

/**************************************************************************//**
 * @brief GPIO Interrupt handler (PB0)
 *        Switches between analog and digital clock modes.
 *****************************************************************************/
void GPIO_EVEN_IRQHandler(void)
{
  /* Acknowledge interrupt */
  GPIO_IntClear(1 << 8);

  /* Toggle clock mode (analog/digital) */
  clockMode = (clockMode == CLOCK_MODE_ANALOG) ? CLOCK_MODE_DIGITAL : CLOCK_MODE_ANALOG;
  updateDisplay = true;
}

/**************************************************************************//**
 * @brief GPIO Interrupt handler (PB1)
 *        Increments the time by one minute.
 *****************************************************************************/
void GPIO_ODD_IRQHandler(void)
{
  /* Acknowledge interrupt */
  GPIO_IntClear(1 << 9);

  /* Increase time by 1 second. */
  curTime++;

  timeIsFastForwarding = true;
  updateDisplay = true;
}


/**************************************************************************//**
 * @brief   Set up PCNT to generate an interrupt every second.
 *
 *****************************************************************************/
void pcntInit(void)
{
  PCNT_Init_TypeDef pcntInit = PCNT_INIT_DEFAULT;

  /* Enable PCNT clock */
  CMU_ClockEnable(cmuClock_PCNT0, true);
  /* Set up the PCNT to count RTC_PULSE_FREQUENCY pulses -> one second */
  pcntInit.mode = pcntModeOvsSingle;
  pcntInit.top = RTC_PULSE_FREQUENCY;
  pcntInit.s1CntDir = false;
  pcntInit.s0PRS = pcntPRSCh2;

  PCNT_Init(PCNT0, &pcntInit);
  
  /* Select PRS as the input for the PCNT */
  PCNT_PRSInputEnable(PCNT0, pcntPRSInputS0, true);
  
  /* Enable PCNT interrupt every second */
  NVIC_EnableIRQ(PCNT0_IRQn);
  PCNT_IntEnable(PCNT0, PCNT_IF_OF);
}


/**************************************************************************//**
 * @brief   This interrupt is triggered at every second by the PCNT
 *
 *****************************************************************************/
void PCNT0_IRQHandler(void)
{
  PCNT_IntClear(PCNT0, PCNT_IF_OF);
  
  pcntIrqCount++;
  
  /* Increase time with 1s */
  if (!(timeIsFastForwarding))
  {
    curTime++;
  }

  /* Notify main loop to redraw clock on display. */
  updateDisplay = true;
}

/**************************************************************************//**
 * @brief  Increments the clock quickly while PB1 is pressed.
 *         A callback is used to update either the analog or the digital clock.
 *
 *****************************************************************************/
void fastForwardTime(void (*drawClock)(struct tm*, bool redraw))
{
  unsigned int i = 0;
  struct tm    *time; 
  
  /* Wait 2 seconds before starting to adjust quickly */
  int waitForPcntIrqCount = pcntIrqCount + 2;

  while (pcntIrqCount != waitForPcntIrqCount)
  {
    /* Return if the button is released */
    if (GPIO_PinInGet(gpioPortC, 9) == 1) {
      timeIsFastForwarding = false;
      return;
    }

    /* Keep updating the second counter while waiting */
    if (updateDisplay)
    {
      time = localtime((time_t const *) &curTime);
      drawClock(time, true);
    }

    EMU_EnterEM2(false);
  }

  /* Keep incrementing the time while the button is held */
  while (GPIO_PinInGet(gpioPortC, 9) == 0)
  {
    if (i % 1000 == 0)
    {
      /* Increase time by 1 minute (60 seconds). */
      curTime += 60;

      time = localtime((time_t const *) &curTime);
      drawClock(time, true);
    }
    i++;
  }
  timeIsFastForwarding = false;
}


#if 0
/**************************************************************************//**
 * @brief  Shows an analog clock on the display.
 *
 *****************************************************************************/
void analogClockShow(bool redraw)
{
  /* Convert time format */
  struct tm *time = localtime((time_t const *) &curTime);

  if (updateDisplay)
  {
    /* Draw clock face to frame buffer */
    analogClockUpdate(time, redraw);
    updateDisplay = false;
    if (timeIsFastForwarding)
    {
      fastForwardTime(analogClockUpdate);
    }
  }
}

#endif
/**************************************************************************//**
 * @brief  Updates the digital clock.
 *
 *****************************************************************************/
void digitalClockUpdate(struct tm *time, bool redraw)
{ 
  char clockString[16];
  
  if (redraw)
  {
    GLIB_setFont(&gc, (GLIB_Font_t *)&GLIB_FontNumber16x20);   
    gc.backgroundColor = White;
    gc.foregroundColor = Black;
    GLIB_clear(&gc);  
  }     
  
  sprintf(clockString, "%02d:%02d:%02d", time->tm_hour, time->tm_min, time->tm_sec);
  GLIB_drawString(&gc, clockString, strlen(clockString), 1, 52, true);

  /* Update display */
  DMD_updateDisplay();
}



/**************************************************************************//**
 * @brief  Shows an digital clock on the display.
 *
 *****************************************************************************/
void digitalClockShow(bool redraw)
{
  /* Convert time format */
  struct tm *time = localtime((time_t const *) &curTime);

  if (updateDisplay)
  {
    digitalClockUpdate(time, redraw);
    updateDisplay = false;
    if (timeIsFastForwarding)
    {
      fastForwardTime(digitalClockUpdate);
    }
  }
}

/**************************************************************************//**
 * @brief  Init si114x sensor
 *
 *****************************************************************************/

void initsi114x(void)
{
	I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;
	bool si1147_status;
	 /* Initialize I2C driver, using standard rate. */
	  I2CDRV_Init(&i2cInit);
	  si1147_status = Si1147_Detect_Device(I2C0, SI1147_ADDR);
	  /*configure prox sensor to enter low power state*/
	 // Si1147_ConfigureDetection(I2C0, SI1147_ADDR, true);
}


/**************************************************************************//**
 * @brief  Main function of clock example.
 *
 *****************************************************************************/
int main(void)
{  
  EMSTATUS status;
  bool redraw;
  ClockMode_t prevClockMode = CLOCK_MODE_DIGITAL;

  uint16_t         uvData;			//SHRENIK
  /* objectDetect is set to true when hand (or object) is detected near
  *  Si1147. We look for rising edge on this because if the board is
  *  continuously detecting an object it may be because it is inside
  *  a briefcase or box and not in use. To prevent battery drain we
  *  do not want to detect this condition as user input.
  */
  int              objectDetect;	//SHRENIK
  
  /* Chip errata */
  CHIP_Init();

  /* Use the 21 MHz band in order to decrease time spent awake.
     Note that 21 MHz is the highest HFRCO band on ZG. */
  CMU_ClockSelectSet( cmuClock_HF, cmuSelect_HFRCO  );
  CMU_HFRCOBandSet( cmuHFRCOBand_21MHz );

  /* Setup GPIO for pushbuttons. */
  gpioSetup();

  initsi114x();//Initiate the proximity detection module


  /* Initialize display module */    
  status = DISPLAY_Init();
  if (DISPLAY_EMSTATUS_OK != status)
    while (true)
      ;

  /* Initialize the DMD module for the DISPLAY device driver. */
  status = DMD_init(0);
  if (DMD_OK != status)
    while (true)
      ;

  status = GLIB_contextInit(&gc);
  if (GLIB_OK != status)
    while (true)
      ;
  
  /* Set PCNT to generate interrupt every second */
  pcntInit();
  
  /* Pre-compete positions for the analog graphics */
  //analogClockInitGraphics();
  digitalClockShow(1);
  /* Enter infinite loop that switches between analog and digitcal clock
   * modes, toggled by pressing the button PB0. */
  while (true)
  {    
    //redraw = (prevClockMode != clockMode);
    //prevClockMode = clockMode;

    Si1147_MeasureUVAndObjectPresent(I2C0, SI1147_ADDR, &uvData, &objectDetect);
    if(objectDetect)
    {
      digitalClockShow(1);
    }
    else
    	DisplayClear();
    /* Sleep between each frame update */
    EMU_EnterEM2(false);
  }
}



