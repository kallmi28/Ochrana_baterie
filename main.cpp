
#ifndef F_CPU
#define F_CPU 1000000UL // 16 MHz clock speed
#endif


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>




#include "lcd.h"
#include "pins.h"
#include "menu_fsm.h"


uint16_t* lo_limit_addr = (uint16_t*)0x00;
uint16_t* hi_limit_addr = (uint16_t*)0x02;

unsigned int adc_value = 0;
uint16_t VOLTAGE_NOW = 0;
uint16_t TURN_UP_VOLTAGE = 0;
uint16_t SHUT_DOWN_VOLTAGE = 0;

uint16_t SHUT_DOWN_LOADED = 0;
uint16_t TURN_UP_LOADED = 0;

uint8_t ADC_START = 0;

enum MENU_STATE LAST_STATE;



void shut_down()
{
	if(SHUT_DOWN_LOADED != SHUT_DOWN_VOLTAGE)
		eeprom_write_word(lo_limit_addr, SHUT_DOWN_VOLTAGE);
	if(TURN_UP_VOLTAGE != TURN_UP_LOADED)
		eeprom_write_word(hi_limit_addr, TURN_UP_VOLTAGE);
	// send signal to NMOS
	
	// testing
	Lcd4_Clear();
	Lcd4_Write_String("SHUTDOWN");
	
	PORTC &= (1 << PC4);

	// testing
	while(1);
}

ISR(ADC_vect)
{
	adc_value = ADCW;
	VOLTAGE_NOW = adc_value;
	ADCSRA |= ((1 << ADSC) | (1 << ADEN) | (1 << ADFR));
	
	if(VOLTAGE_NOW <= SHUT_DOWN_VOLTAGE)
		shut_down();
	
	// read conversion value
	// compare with lower limit
		// if lower, then shut down
}

ISR(TIMER1_OVF_vect)
{
	if(ADC_START++ & 0x03)
		ADCSRA  |= (1<<ADSC);
	// inc ADC counter
		// if at some value, start conversion
	
}


void ADC_Init ()
{
	ADCSRA  = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
	// Set ADCSRA Register with division factor 32
	ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADIF);
	ADMUX=0x43;	//Binary equivalent of 0100 0011 -> AVcc as ref, channel 3
}

void Timer_Init()
{
	TIMSK |= (1 << TOIE1);
	TCNT1 = 0;
	TCCR1B |= (1 << CS11);	
}


//*

int main (void)
{
	TURN_UP_VOLTAGE = eeprom_read_word(hi_limit_addr);
	SHUT_DOWN_VOLTAGE = eeprom_read_word(lo_limit_addr);
	TURN_UP_LOADED = TURN_UP_VOLTAGE;
	SHUT_DOWN_LOADED = SHUT_DOWN_VOLTAGE;
	DDRD = 0xF0;
	DDRB = 0xC0;
	DDRC |= (1 << PC4);
	PORTC |= 1 << PC4;
	
		Lcd4_Init();
		Lcd4_Clear();
	
	
	ADC_Init();

	ADCSRA  |= (1<<ADSC);
	while(ADCSRA & (1 << ADSC));
	VOLTAGE_NOW = ADCW;	
	if(VOLTAGE_NOW <= TURN_UP_VOLTAGE)
		shut_down();
	
		
	enum BUTTON BUTTON1;
	enum BUTTON BUTTON2;
	enum BUTTON BUTTON3;

	enum MENU_STATE NEXT_STATE;
	enum MENU_STATE CURRENT_STATE;

	Init_FSM(&BUTTON1, &BUTTON2, &BUTTON3, &CURRENT_STATE, &NEXT_STATE);
	Print_Menu(&BUTTON1, &BUTTON2, &BUTTON3, &CURRENT_STATE, &NEXT_STATE, &SHUT_DOWN_VOLTAGE, &VOLTAGE_NOW, &TURN_UP_VOLTAGE);

	LAST_STATE = CURRENT_STATE;
	sei();

	while(1)
	{
		if((PIND & (1<<PD0))) BUTTON1 = TRUE;
		if((PIND & (1<<PD1))) BUTTON2 = TRUE;
		if((PIND & (1<<PD2))) BUTTON3 = TRUE;

		Move_Between_States(&BUTTON1, &BUTTON2, &BUTTON3, &CURRENT_STATE, &NEXT_STATE, &SHUT_DOWN_VOLTAGE, &TURN_UP_VOLTAGE);
		if(LAST_STATE != CURRENT_STATE)
			Print_Menu(&BUTTON1, &BUTTON2, &BUTTON3, &CURRENT_STATE, &NEXT_STATE, &SHUT_DOWN_VOLTAGE, &VOLTAGE_NOW, &TURN_UP_VOLTAGE);
		// doesnt print change in voltage when in state NOW_VOLT
		
		
		BUTTON1 = FALSE;
		BUTTON2 = FALSE;
		BUTTON3 = FALSE;
		
		LAST_STATE = CURRENT_STATE;
		
	}
}
