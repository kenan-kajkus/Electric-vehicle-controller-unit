/*
 * MotorPwm.h
 *
 * Created: 23.04.2018 08:04:57
 *  Author: Kenan Kajkus
 */ 


#ifndef MotorPwm
#define MotorPwm

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "pins.h"
#include "UartMessage.h"

void initMotordriver(UartMessage * uartMessage);
void initPwmMotor();
void changeSpeed();
void changeSpeedLeft(long a);
void changeSpeedRight(long b);
void setForward();
void setBackward();
long map(uint8_t x);

#endif /* MotorPWM_H */