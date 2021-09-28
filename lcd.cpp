#ifndef F_CPU
#define F_CPU 1000000UL // 16 MHz clock speed
#endif


#include <avr/io.h>
#include <util/delay.h>


#include "pins.h"
#include "lcd.h"



void Lcd4_Port(unsigned char nibble)
{
	PORTD = (nibble << 4) | (PORTD & 0xf);
}


void Lcd4_Clear()
{
	Lcd4_Cmd(0);
	Lcd4_Cmd(1);
}


void Lcd4_Cmd(unsigned char command)
{

	PORTB &= ~ (1 << RS);		// RS -> 0
	Lcd4_Port(command);
	PORTB |= (1 << EN);			// EN -> 1
	_delay_ms(1);
	PORTB &= ~ (1 << EN);		// EN -> 0
	_delay_ms(1);
}

void Lcd4_Shift_Right(void)
{
	Lcd4_Cmd(0x01);
	Lcd4_Cmd(0x0C);
}

void Lcd4_Shift_Left(void)
{
	Lcd4_Cmd(0x01);
	Lcd4_Cmd(0x08);
}

void Lcd4_Set_Cursor(unsigned char line, unsigned char column)
{
	unsigned char temp = 0x80 + line* 0x40 + column;

	Lcd4_Cmd(temp >> 4);
	Lcd4_Cmd(temp & 0x0f);
}

void Lcd4_Init()
{
	Lcd4_Port(0x00);
	_delay_ms(20);
	///////////// Reset process from datasheet /////////
	Lcd4_Cmd(0x03);
	_delay_ms(5);
	Lcd4_Cmd(0x03);
	_delay_ms(11);
	Lcd4_Cmd(0x03);
	/////////////////////////////////////////////////////
	Lcd4_Cmd(0x02);
	Lcd4_Cmd(0x02);
	Lcd4_Cmd(0x08);
	Lcd4_Cmd(0x00);
	Lcd4_Cmd(0x0C);
	Lcd4_Cmd(0x00);
	Lcd4_Cmd(0x06);
}

void Lcd4_Write_Char(unsigned char data)
{	
	PORTB |= (1<<RS);				// RS -> 1
	Lcd4_Port((data & 0xf0)>> 4);	// Data transfer
	PORTB |= (1 << EN);				// EN -> 1
	_delay_ms(1);
	PORTB &= ~ (1 << EN);			// EN -> 0
	_delay_ms(1);
	Lcd4_Port(data & 0x0f);
	PORTB |= (1 << EN);				// EN -> 1
	_delay_ms(1);
	PORTB &= ~ (1 << EN);			// EN -> 0
	_delay_ms(1);	
}

void Lcd4_Write_String(const char *str)
{
	int i = 0;
	while(str[i] != 0)
	Lcd4_Write_Char(str[i++]);
}


void Lcd4_Write_Float(float number)
{
	char tmp[16];
	dtostrf(number, 5, 2, tmp);
	Lcd4_Write_String(tmp);
}

void Lcd4_Write_Int(int number)
{
	char tmp[16];
	itoa(number, tmp, 10);
	Lcd4_Write_String(tmp);
}

void Lcd4_Write_ULong(unsigned long int number)
{
	char tmp[16];
	ultoa(number, tmp, 10);
	Lcd4_Write_String(tmp);
}


