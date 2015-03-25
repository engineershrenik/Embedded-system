/******************************************************************************
 *
 * Copyright (C) 2013 Microchip Technology Inc. and its
 *                    subsidiaries (“Microchip”).
 *
 * All rights reserved.
 *
 * You are permitted to use the Aurea software, GestIC API, and other
 * accompanying software with Microchip products.  Refer to the license
 * agreement accompanying this software, if any, for additional info regarding
 * your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
 * MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP, SMSC, OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH
 * OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY FOR ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES, OR OTHER SIMILAR COSTS.
 *
 ******************************************************************************/
#include "console.h"

/* Human readable strings for the gestures */
/*
char *gestures[] = {
    "-                       ",
    "Flick West > East       ",
    "Flick East > West       ",
    "Flick South > North     ",
    "Flick North > South     ",
    "Circle clockwise        ",
    "Circle counter-clockwise"
};
*/
/* Human readable strings for the gestures */
char *gestures[] = {
    "DNULL",
    "DRIGHT",
    "DLEFT",
    "DUP",
    "DDOWN",
    "CCW",
    "CCCW"
};

char tcpData[10];
int lastz;
void init_device(data_t *data)
{
    /* Bitmask later used for starting a stream with
     * SD-, position- and gesture-data
     */
    const int stream_flags = gestic_data_sd | gestic_data_position |
            gestic_data_gesture | gestic_data_touch;

    /* Allocate a new gestic_t-instance */
    data->gestic = gestic_create();

    /* Initialize the gestic_t-instance */
    gestic_initialize(data->gestic);

    /* Open a connection to the device */
    if(gestic_open(data->gestic) < 0) {
        fprintf(stderr, "Could not open connection to device.\n");
        exit(-1);
    }

    /* Get pointers to the result-buffers */
    data->gestic_pos = gestic_get_position(data->gestic, 0);
    data->gestic_sd = gestic_get_sd(data->gestic, 0);
    data->gestic_calib = gestic_get_calibration(data->gestic, 0);
    data->gestic_gesture = gestic_get_gesture(data->gestic, 0);
    data->gestic_touch = gestic_get_touch(data->gestic, 0);
    data->gestic_air_wheel = gestic_get_air_wheel(data->gestic, 0);

    /* Reset the device to the default state:
     * - Automatic calibration enabled
     * - All frequencies allowed
     * - Approach detection enabled for power saving
     * - Enable all gestures ( bit 1 to 6 set to 1 = 126 )
     */
    if(gestic_set_auto_calibration(data->gestic, data->auto_calib, 100) < 0 ||
       gestic_select_frequencies(data->gestic, gestic_all_freq, 100) < 0 ||
       gestic_set_approach_detection(data->gestic, 1, 100) < 0 ||
       gestic_set_enabled_gestures(data->gestic, 126, 100) < 0)
    {
        fprintf(stderr, "Could not reset device to default state.\n");
        exit(-1);
    }

    /* Start the data-stream with the bitmask defined above */
    if(gestic_data_stream(data->gestic, stream_flags, 100) < 0) {
        fprintf(stderr, "Could not start data-streaming from device.\n");
        exit(-1);
    }
}

void free_device(data_t *data)
{
    /* Close the connection to the device */
    gestic_close(data->gestic);

    /* Release resources that were associated with the gestic_t-instance */
    gestic_cleanup(data->gestic);

    /* Release the gestic_t-instance itself */
    gestic_free(data->gestic);
}

int counts=0;
void update_device(data_t *data)
{
    int i;
	

    /* Abbreviations for the electrodes */
    const char source[] = { 'S', 'W', 'N', 'E', 'C' };


    while(gestic_data_stream_update(data->gestic, NULL) == 0)
    {
        /* Print update of the position */
        gotoxy(0, 4);
        if(data->gestic_pos != NULL)
        {    printf("Position:         X %5d   Y %5d   Z %5d   \n",
                   data->gestic_pos->x, data->gestic_pos->y,
                   data->gestic_pos->z);
		/*
		counts++;
		if (counts == 10)
		{
			if((lastz != data->gestic_pos->z))
			{
			tcpData[0]='Z';
			sprintf(&tcpData[1],"%d",data->gestic_pos->z);
			tcpSendData(tcpData);
			lastz = data->gestic_pos->z;
			counts = 0;
			}
		}*/
		}
        else
            printf("Position:         Not available\n");

        /* Print update of gestures */
        gotoxy(0, 5);
        if(data->gestic_gesture != NULL) {
            /* Remember last gesture and reset it after 1s = 200 updates */
            if(data->gestic_gesture->gesture > 0 && data->gestic_gesture->gesture <= 6)
                data->last_gesture = data->gestic_gesture->gesture;
            else if(data->gestic_gesture->last_event > 1)	//Shrenik
                data->last_gesture = 0;

            printf("Gesture:          %s \n", gestures[data->last_gesture]);
			//*tcpData = (char *)gestures[data->last_gesture];
			if(strcmp(gestures[data->last_gesture],"DNULL"))
			{
				tcpSendData(gestures[data->last_gesture]);

			}
			else if((lastz != data->gestic_pos->z))
			{
				if(((lastz-data->gestic_pos->z) > 1000) | ((data->gestic_pos->z - lastz) > 1000))
				{
				tcpData[0]='Z';
				sprintf(&tcpData[1],"%d",data->gestic_pos->z);
				// tcpSendData(tcpData);
				lastz = data->gestic_pos->z;
				//counts = 0;
				//Sleep(10);
				}
			}

        } else {
            printf("Gesture:          Not available\n");
        }

        /* Print update of touch */
        gotoxy(0, 6);
        printf("Touch:            ");
        for(i = 0; i < 5; ++i) {
            if(data->gestic_touch->flags & (1<<i))
                printf("%c ", source[i]);
        }
        printf("           \n");

        /* Print update of AirWheel */
        gotoxy(0, 7);
        if(data->gestic_air_wheel != NULL) {
            printf("Air Wheel:        %d   \n", data->gestic_air_wheel->counter);
        } else {
            printf("Air Wheel:        Not available\n");
        }

        /* Print update of Signal Deviation */
        gotoxy(0, 8);
        if(data->gestic_sd != NULL) {
            printf("Signal Deviation:");
            for(i = 0; i < 5; ++i)
                printf(" %c %5.0f  ", source[i], data->gestic_sd->channel[i]);

            if(data->gestic_calib != NULL)
                printf("\nLast Calibration: %7d",
                       data->gestic_calib->last_event);
        } else {
            printf("Signal Deviation: Not available\n");
        }
    }
}

void switch_auto_calib(data_t *data)
{
    /* Try to swith autocalibration with a timeout of 100 ms */
    int new_mode = !data->auto_calib;
    if(gestic_set_auto_calibration(data->gestic, new_mode, 100) != 0)
        return;
    data->auto_calib = new_mode;
}

void calibrate_now(data_t *data)
{
    /* Try to force calibration with a timeout of 100 ms */
    gestic_force_calibration(data->gestic, 100);
}

void switch_touch_detect(data_t *data) {
    int new_mode = !data->touch_detect;
    if(gestic_set_touch_detection(data->gestic, new_mode, 100) != 0)
        return;
    data->touch_detect = new_mode;
}

void switch_air_wheel(data_t *data) {
    int new_mode = !data->air_wheel;
    if(gestic_set_air_wheel_enabled(data->gestic, new_mode, 100) != 0)
        return;
    data->air_wheel = new_mode;
}
