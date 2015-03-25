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
#pragma once

#include <gestic_api.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#define FLICK_TIMEOUT 200

typedef struct 
{
    int running;
    int menu_current;
    int auto_calib;
    int last_gesture;
    int touch_detect;
    int air_wheel;

    gestic_t *gestic;
    gestic_position_t *gestic_pos;
    gestic_gesture_t *gestic_gesture;
    gestic_signal_t *gestic_sd;
    gestic_calib_t *gestic_calib;
    gestic_touch_t *gestic_touch;
    gestic_air_wheel_t *gestic_air_wheel;
} data_t;

void gotoxy(int x, int y);
void init_data(data_t *data);
void update_menu(data_t *data);

void init_device(data_t *data);
void free_device(data_t *data);
void update_device(data_t *data);

void switch_auto_calib(data_t *data);
void calibrate_now(data_t *data);

void switch_touch_detect(data_t *data);
void switch_air_wheel(data_t *data);

int tcpInit(void);
int tcpSendData(char *uData);
