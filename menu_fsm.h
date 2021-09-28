/*
 * menu_fsm.h
 *
 * Created: 28-Apr-18 20:10:55
 *  Author: abc
 */ 




#ifndef MENU_FSM_H_
#define MENU_FSM_H_

#include "globals.h"
#include <avr/io.h>

	

void Move_Between_States (enum BUTTON *BUTTON1, enum BUTTON *BUTTON2, enum BUTTON *BUTTON3, enum MENU_STATE *CURRENT_STATE, enum MENU_STATE *NEXT_STATE, uint16_t *sh_volt, uint16_t *turn_volt);
void Init_FSM (enum BUTTON *BUTTON1, enum BUTTON *BUTTON2, enum BUTTON *BUTTON3, enum MENU_STATE *CURRENT_STATE, enum MENU_STATE *NEXT_STATE);
void Print_Menu(enum BUTTON *BUTTON1, enum BUTTON *BUTTON2, enum BUTTON *BUTTON3, enum MENU_STATE *CURRENT_STATE, enum MENU_STATE *NEXT_STATE, uint16_t *sh_volt, uint16_t *now_volt, uint16_t *turn_volt);


// testing
void foo (enum BUTTON *BUTTON_1, enum BUTTON *BUTTON_2, enum BUTTON *BUTTON_3, enum MENU_STATE *CURRENT_STATE, enum MENU_STATE *NEXT_STATE, uint16_t *sh_volt, uint16_t *now_volt, uint16_t *turn_volt);
void test (enum BUTTON *BUTTON1, enum BUTTON *BUTTON2, enum BUTTON *BUTTON3, enum MENU_STATE *CURRENT_STATE, enum MENU_STATE *NEXT_STATE, uint16_t *sh_volt, uint16_t *now_volt, uint16_t *turn_volt);


#endif /* MENU_FSM_H_ */

