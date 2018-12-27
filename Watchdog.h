/*
 * Watchdog.h
 *
 * Created: 30.04.2018 19:46:51
 *  Author: Kenan
 */ 


#ifndef WATCHDOG_H_
#define WATCHDOG_H_
#include "bollerwagen.h"
#include <avr/wdt.h>

// Initialize watchdog with a x second interrupt time
void watchdog_init();

// Reset watchdog. at least every x seconds after the
// first watchdog_init or AVR will go into emergency procedures.
inline void watchdog_reset() { wdt_reset(); }



#endif /* WATCHDOG_H_ */