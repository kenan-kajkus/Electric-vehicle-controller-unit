/*
 * emergencyStop.c
 *
 * Created: 16.07.2020 12:07:08
 *  Author: Kenan Kajkus
 */ 
 
#include <avr/interrupt.h>
#include "emergencyStop.h"

void startEmergencyStop()
{
	// TIMER 1 for interrupt frequency 2 Hz:
	cli(); // stop interrupts
	TCCR1A = 0; // set entire TCCR1A register to 0
	TCCR1B = 0; // same for TCCR1B
	TCNT1  = 0; // initialize counter value to 0
	// set compare match register for 2 Hz increments
	OCR1A = 31249; // = 16000000 / (256 * 2) - 1 (must be <65536)
	// turn on CTC mode
	TCCR1B |= (1 << WGM12);
	// Set CS12, CS11 and CS10 bits for 256 prescaler
	TCCR1B |= (1 << CS12) | (0 << CS11) | (0 << CS10);
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	sei(); // allow interrupts

	//Testpin
	DDRC |= (1<<PINC6);
}

ISR(TIMER1_COMPA_vect)
{
	/* Interrupt action every 2Hz*/
	/*Toggles pin for testing*/
	PORTC ^= (1<<PINC6);
	
	/* for later use
	if(!(PINL & (1<<PL0))&&((PINL & (1<<PL2)))){
		return;
		}else{
		cli();
		wdt_enable (WDTO_15MS);
		while (1);
	}*/
}