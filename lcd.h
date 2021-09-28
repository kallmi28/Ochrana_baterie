/*
 * lcd.h
 *
 * Created: 25-Apr-18 22:17:28
 *  Author: abc
 */ 
#include <stdlib.h>

#ifndef LCD_H_
#define LCD_H_

// Printing
void Lcd4_Write_String(const char *str);
void Lcd4_Write_Float(float number);
void Lcd4_Write_Int(int number);
void Lcd4_Write_ULong(unsigned long int number);
void Lcd4_Cmd(unsigned char command);
void Lcd4_Write_Char(unsigned char a);

// Commands and data input setting
void Lcd4_Init();
void Lcd4_Clear();
void Lcd4_Set_Cursor(unsigned char line, unsigned char column);
void Lcd4_Shift_Right(void);
void Lcd4_Shift_Left(void);
void Lcd4_Port(unsigned char a);


#endif /* LCD_H_ */