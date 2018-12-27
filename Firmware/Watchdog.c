/*
 * Watchdog.c
 *
 * Created: 30.04.2018 19:46:30
 *  Author: Kenan
 */ 


#include "Watchdog.h"
//Time to watch

#define WDTO_NS WDTO_250MS


void watchdog_init(){
	watchdog_reset();
	//disables global interrupts
	cli();
	_WD_CONTROL_REG = (1 << _WD_CHANGE_BIT) | (1 << WDE);
	_WD_CONTROL_REG = (1<<WDIE) | (WDTO_NS & 0x07) | ((WDTO_NS & 0x08) << 2);
	//enables global interrupts again
	sei();
	//reseting watchdog timer for the first time after initializing
	watchdog_reset();
}