/*
 * lenkung.h
 *
 * Created: 10.05.2018 19:09:53
 *  Author: Kenan
 */ 


#ifndef LENKUNG_H_
#define LENKUNG_H_

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "pins.h"
#include "UartMessage.h"

void initLenkungPwm(UartMessage * message);
void changeLenkung();

extern int wohin;


#endif /* LENKUNG_H_ */