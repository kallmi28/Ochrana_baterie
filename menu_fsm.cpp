/*
  menu_fsm.cpp
 
  Created: 29-Apr-18 14:37:15
   Author: abc
 */ 

#include "menu_fsm.h"
#include "lcd.h"

void Move_Between_States (enum BUTTON *BUTTON_1, enum BUTTON *BUTTON_2, enum BUTTON *BUTTON_3, enum MENU_STATE *CURRENT_STATE, enum MENU_STATE *NEXT_STATE, uint16_t* sh_volt, uint16_t* turn_volt)
{
	switch(*CURRENT_STATE)
	{
		case NOW_VOLT:
			if(*BUTTON_1 == TRUE)
				*NEXT_STATE = NOW_VOLT_B1;
			else if(*BUTTON_2 == TRUE)
				*NEXT_STATE = NOW_VOLT_B2;
		break;
		case NOW_VOLT_B1:
			if(*BUTTON_1 == FALSE)
				*NEXT_STATE = SHT_DWN_VOLT;
		break;
		case NOW_VOLT_B2:
			if(*BUTTON_2 == FALSE)
				*NEXT_STATE = TRN_UP_VOLT;
		break;
		case SHT_DWN_VOLT:
			if(*BUTTON_1 == TRUE)
				*NEXT_STATE = SHT_DWN_VOLT_B1;
			else if(*BUTTON_2 == TRUE)
				*NEXT_STATE = SHT_DWN_VOLT_B2;
			else if(*BUTTON_3 == TRUE)
				*NEXT_STATE = SHT_DWN_VOLT_B3;
		break;
		case SHT_DWN_VOLT_B1:
			if(*BUTTON_1 == FALSE)
				*NEXT_STATE = TRN_UP_VOLT;
		break;
		case SHT_DWN_VOLT_B2:
			if(*BUTTON_2 == FALSE)
				*NEXT_STATE = NOW_VOLT;
		break;
		case SHT_DWN_VOLT_B3:
			if(*BUTTON_3 == TRUE)
				*NEXT_STATE = CHNG_SHT_DWN_VOLT;
		break;
		case TRN_UP_VOLT:
			if(*BUTTON_1 == TRUE)
				*NEXT_STATE = TRN_UP_VOLT_B1;
			else if(*BUTTON_2 == TRUE)
				*NEXT_STATE = TRN_UP_VOLT_B2;
			else if(*BUTTON_3 == TRUE)
				*NEXT_STATE = TRN_UP_VOLT_B3;
		break;
		case TRN_UP_VOLT_B1:
			if(*BUTTON_1 == FALSE)
				*NEXT_STATE = NOW_VOLT;
		break;
		case TRN_UP_VOLT_B2:
			if(*BUTTON_2 == FALSE)
				*NEXT_STATE = SHT_DWN_VOLT;
		break;
		case TRN_UP_VOLT_B3:
			if(*BUTTON_3 == FALSE)
				*NEXT_STATE = CHNG_TRN_UP_VOLT;
		break;
		case CHNG_TRN_UP_VOLT:
			if(*BUTTON_1 == TRUE)
				*NEXT_STATE = CHNG_TRN_UP_VOLT_B1;
			else if(*BUTTON_2 == TRUE)
				*NEXT_STATE = CHNG_TRN_UP_VOLT_B2;
			else if(*BUTTON_3 == TRUE)
				*NEXT_STATE = CHNG_TRN_UP_VOLT_B3;
		break;
		case CHNG_TRN_UP_VOLT_B1:
			if(*BUTTON_1 == FALSE)
				*NEXT_STATE = CHNG_TRN_UP_VOLT;
		break;
		case CHNG_TRN_UP_VOLT_B2:
			if(*BUTTON_2 == FALSE)
				*NEXT_STATE = CHNG_TRN_UP_VOLT;
		break;
		case CHNG_TRN_UP_VOLT_B3:
			if(*BUTTON_3 == FALSE)
				*NEXT_STATE = TRN_UP_VOLT;
		break;
		case CHNG_SHT_DWN_VOLT:
			if(*BUTTON_1 == TRUE)
				*NEXT_STATE = CHNG_SHT_DWN_VOLT_B1;
			else if(*BUTTON_2 == TRUE)
				*NEXT_STATE = CHNG_SHT_DWN_VOLT_B2;
			else if(*BUTTON_3 == TRUE)
				*NEXT_STATE = CHNG_SHT_DWN_VOLT_B3;
		break;
		case CHNG_SHT_DWN_VOLT_B1:
			if(*BUTTON_1 == FALSE)
				*NEXT_STATE = CHNG_SHT_DWN_VOLT;
		break;
		case CHNG_SHT_DWN_VOLT_B2:
			if(*BUTTON_2 == FALSE)
				*NEXT_STATE = CHNG_SHT_DWN_VOLT;
		break;
		case CHNG_SHT_DWN_VOLT_B3:
			if(*BUTTON_3 == FALSE)
				*NEXT_STATE = SHT_DWN_VOLT;
		break;
		default:
		break;
	}
	
	if(*CURRENT_STATE == CHNG_SHT_DWN_VOLT)
	{
		if(*NEXT_STATE == CHNG_SHT_DWN_VOLT_B1)
			*sh_volt -= 6;
		else if(*NEXT_STATE == CHNG_SHT_DWN_VOLT_B2)
			*sh_volt += 6;
			
		if(*sh_volt >= 1023) *sh_volt = 1023;
		else if(*sh_volt <= 0) *sh_volt = 0;
	}
	else if(*CURRENT_STATE == CHNG_TRN_UP_VOLT)
	{
		if(*NEXT_STATE == CHNG_TRN_UP_VOLT_B1)
			*turn_volt -= 6;
		else if(*NEXT_STATE == CHNG_TRN_UP_VOLT_B2)
			*turn_volt += 6;
		
		if(*turn_volt >= 1023) *turn_volt = 1023;
		else if (*turn_volt <= 0) *turn_volt = 0;
	}
	
	*CURRENT_STATE = *NEXT_STATE;	
}

void Init_FSM (enum BUTTON *BUTTON_1, enum BUTTON *BUTTON_2, enum BUTTON *BUTTON_3, enum MENU_STATE *CURRENT_STATE, enum MENU_STATE *NEXT_STATE)
{
	*CURRENT_STATE = NOW_VOLT;
	*NEXT_STATE = NOW_VOLT;
	*BUTTON_1 = FALSE;
	*BUTTON_2 = FALSE;
	*BUTTON_3 = FALSE;
}

void Print_Menu(enum BUTTON *BUTTON_1, enum BUTTON *BUTTON_2, enum BUTTON *BUTTON_3, enum MENU_STATE *CURRENT_STATE, enum MENU_STATE *NEXT_STATE, uint16_t *sh_volt, uint16_t *now_volt, uint16_t *turn_volt)
{

	
	switch(*CURRENT_STATE)
	{
		case NOW_VOLT:
			Lcd4_Set_Cursor(1,0);
			Lcd4_Write_Char(' ');
			Lcd4_Set_Cursor(1,15);
			Lcd4_Write_Char(' ');
			
			Lcd4_Set_Cursor(0,0);
			Lcd4_Write_Char(0xf7);
			Lcd4_Set_Cursor(0,15);
			Lcd4_Write_Char(0xf6);
			Lcd4_Set_Cursor(0,1);
			Lcd4_Write_String("VOLTAGE NOW   ");
			Lcd4_Set_Cursor(1, 5);
			Lcd4_Write_Float(*now_volt * 18/1023.0);
	
		break;
		case SHT_DWN_VOLT:
			Lcd4_Set_Cursor(1,0);
			Lcd4_Write_Char(' ');
			Lcd4_Set_Cursor(1,15);
			Lcd4_Write_Char(' ');
			
			Lcd4_Set_Cursor(0,0);
			Lcd4_Write_Char(0xf7);
			Lcd4_Set_Cursor(0,15);
			Lcd4_Write_Char(0xf6);
			Lcd4_Set_Cursor(0,1);
			Lcd4_Write_String("LOWER LIMIT   ");		
			Lcd4_Set_Cursor(1, 5);
			Lcd4_Write_Float(*sh_volt* 18/1023.0);		
		break;
		case TRN_UP_VOLT:
			Lcd4_Set_Cursor(1,0);
			Lcd4_Write_Char(' ');
			Lcd4_Set_Cursor(1,15);
			Lcd4_Write_Char(' ');
		
		
			Lcd4_Set_Cursor(0,0);
			Lcd4_Write_Char(0xf7);
			Lcd4_Set_Cursor(0,15);
			Lcd4_Write_Char(0xf6);
			Lcd4_Set_Cursor(0,1);
			Lcd4_Write_String("UPPER LIMIT   ");

			
			Lcd4_Set_Cursor(1, 5);
			Lcd4_Write_Float(*turn_volt* 18/1023.0);
		break;
		case CHNG_SHT_DWN_VOLT:
			Lcd4_Set_Cursor(0,0);
			Lcd4_Write_Char(' ');
			Lcd4_Set_Cursor(0,15);
			Lcd4_Write_Char(' ');
			Lcd4_Set_Cursor(1, 0);
			Lcd4_Write_Char(0xf7);
			Lcd4_Set_Cursor(1,15);
			Lcd4_Write_Char(0xf6);
			
			Lcd4_Set_Cursor(1, 5);
			Lcd4_Write_Float(*sh_volt* 18/1023.0);		
		break;
		case CHNG_TRN_UP_VOLT:
			Lcd4_Set_Cursor(0,0);
			Lcd4_Write_Char(' ');
			Lcd4_Set_Cursor(0,15);
			Lcd4_Write_Char(' ');
			Lcd4_Set_Cursor(1, 0);
			Lcd4_Write_Char(0xf7);
			Lcd4_Set_Cursor(1,15);
			Lcd4_Write_Char(0xf6);
			
			Lcd4_Set_Cursor(1, 5);
			Lcd4_Write_Float(*turn_volt* 18/1023.0);
		
		break;
		default:
		break;
	}
	
	
}


void foo (enum BUTTON *BUTTON_1, enum BUTTON *BUTTON_2, enum BUTTON *BUTTON_3, enum MENU_STATE *CURRENT_STATE, enum MENU_STATE *NEXT_STATE, uint16_t *sh_volt, uint16_t *now_volt, uint16_t *turn_volt)
{
	Move_Between_States(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, turn_volt);
	Print_Menu(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
		
}

void test (enum BUTTON *BUTTON_1, enum BUTTON *BUTTON_2, enum BUTTON *BUTTON_3, enum MENU_STATE *CURRENT_STATE, enum MENU_STATE *NEXT_STATE, uint16_t *sh_volt, uint16_t *now_volt, uint16_t *turn_volt)
 {
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); //now volt
	*BUTTON_1 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_1 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // lower
	*BUTTON_1 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_1 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // upper
	*BUTTON_1 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_1 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // now volt


	*BUTTON_2 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_2 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // upper
	*BUTTON_2 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_2 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // lower
	*BUTTON_2 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_2 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // now
	*BUTTON_2 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_2 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // upper
	
	
	*BUTTON_3 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_3 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // change upper
	*BUTTON_1 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_1 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // -0.1
	*BUTTON_1 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_1 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // -0.1
	
	*BUTTON_3 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_3 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // upper
	
	*BUTTON_2 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_2 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // lower
	*BUTTON_2 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_2 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // now
	
	*BUTTON_3 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_3 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // now (nothing happened)
	*BUTTON_3 = TRUE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt);
	*BUTTON_3 = FALSE;
	foo(BUTTON_1, BUTTON_2, BUTTON_3, CURRENT_STATE, NEXT_STATE, sh_volt, now_volt, turn_volt); // now (nothing happened)
	
}