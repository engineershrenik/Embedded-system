

#ifndef _HDG12864_H_
#define _HDG12864_H_
#endif
/*
LCD DATA port----PORT B
CTRL port------PORT C
RS-------PC1
RW-------PC0
EN-------PC2
*/

#ifdef _HDG12864_H_


#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

//Macros
#define 	RW	PC0	//Read/Write Select 0-Write to display, 1-Read from display
#define 	RS	PC1	//Register Select 0 - Command Register Select, 1 - Data register Select
#define 	EN	PC2	//Enable Display Signal
#define 	LCD_CMD_PORT	PORTC
#define		LCD_DATA_PORT	PORTB

//#define 	WRITE_DISPLAY()	( PORTC &=~ ( 1 << RW))
#define 	CMD_WRITE_EN()	( LCD_CMD_PORT = ( 0 << RS) | ( 0 << RW) | ( 1 << EN) )
#define 	DATA_WRITE_EN()	( LCD_CMD_PORT = ( 1 << RS) | ( 0 << RW) | ( 1 << EN) )
#define 	CMD_WRITE_DS()	( LCD_CMD_PORT = ( 0 << RS) | ( 0 << RW) | ( 0 << EN) )
#define 	DATA_WRITE_DS()	( LCD_CMD_PORT = ( 1 << RS) | ( 0 << RW) | ( 0 << EN) )

void initLCD( void);
void writeCmd( uint8_t uCmd);
void writeData(	uint8_t uData);
void setRow( uint8_t uRowAddr);
void setColumn( uint8_t uColumnAddr);
void writeChar(uint8_t uChar);
void writeString(uint8_t x, uint8_t y,uint8_t *uString);

#endif //_HDG12864_H_
