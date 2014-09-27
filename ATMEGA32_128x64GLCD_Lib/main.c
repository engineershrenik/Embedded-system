/*
Project - Interfacing 128*64 Graphics LCD to ATMEGA32
Author: Shrenik Shikhare
Email:  engineershrenik@gmail.com
date:   25/9/2014
homepage:    embeddlinux.blogspot.in
 
compiler: avr-gcc
Copyright (C) <2014>  <embeddlinux.blogspot.in>
 
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
 
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


 


#include <inttypes.h>
//#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
//#include <util/delay.h>
#include "HDG12864FLcd.h"

//uint8_t 
int main()
 { 
   // Write your code here
    DDRB |= 0xFF;
    DDRC |= 0xFF;
    initLCD();
    writeString(40,3,"SHRENIK's");
    writeString(20,4,"LCD DISPLAY LIB");
    
   while (1)
   {
      //PORTB ^= 0xFF;
      //_delay_ms();
   }
   return 0;
 }