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


#include "HDG12864FLcd.h"
#include "Fonts.h"
#include <string.h>

//Initializes Graphics LCD
void initLCD( void)
{

   //writeCmd(0xA5);	//Set All Points
   writeCmd(0xAF);	//Display ON
   //writeCmd(0x40);	//Display RAM start address 0b000000 | 0b01
   //writeCmd(0x0F);
   writeCmd(0xA6);	//Normal Display
   //writeCmd(0xA0);
   //writeCmd(0xC8);  
   
}

//This function writes single character from fonts and a white space of single column
void writeChar(uint8_t uChar)
{
   int i;
   for ( i = 4; i >= 0; i--)
   {
      writeData(Font5x7[ ((uChar - 32)*5)+i]);	//Get Correspondent Hex Values needed to represent ASCII char from Fonts
	 //writeCmd(0xE0);
   }
   writeData(0x00);	//Space after each character print
}

//This function writes string on display on specified x (Column), y address(Row)
void writeString(uint8_t x, uint8_t y,uint8_t *uString)
{
      setRow(y);
      uString = strrev(uString);
  
  
      setColumn(x);
      while(*uString)
      {
	writeChar(*uString++);
      }
}

//This function sets RAM address to specified ROW number.
void setRow( uint8_t uRowAddr)
{
   uRowAddr = uRowAddr | 0xB0;
   writeCmd( uRowAddr);
}

//This function sets column address from 128 columns
void setColumn( uint8_t uColumnAddr)
{
   uint8_t uLowAddr, uHighAddr;
   uHighAddr =	0x10 | (( uColumnAddr &0xF0) >> 4);  
   uLowAddr = ( uColumnAddr & 0x0F);
   //writeCmd(0xE1);
   
   writeCmd( uHighAddr);
   writeCmd( uLowAddr);
}

//Write Command to LCD
void writeCmd( uint8_t uCmd)
{
   LCD_DATA_PORT = uCmd;
   CMD_WRITE_EN();
   _delay_ms(1);
   CMD_WRITE_DS();
   //_delay_ms(50); //Need to enable in real setup for simulation it adds more delay
   
}

//Write Data to LCD
void writeData(	uint8_t uData)
{
   LCD_DATA_PORT = uData;
   DATA_WRITE_EN();
   _delay_ms(1);
   DATA_WRITE_DS();
   //_delay_ms(50); //Need to enable in real setup for simulation it adds more delay  
   
}

