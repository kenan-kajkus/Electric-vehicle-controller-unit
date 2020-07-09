/*
 * MotorPwm.h
 *
 * Created: 23.04.2018 08:04:57
 *  Author: Kenan
 */ 


#ifndef MotorPwm
#define MotorPwm

#define F_CPU 16000000UL// Clock Speed

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include "pins.h"

typedef struct
{
		uint8_t speedLeft;
		uint8_t speedRight;
		uint8_t dir;
}Motors;

void initMotordriver();
void initPwmMotor();
void changeSpeed(uint8_t speed);
void changeSpeedLR(uint8_t left, uint8_t right);
void changeSpeedLeft(uint8_t a);
void changeSpeedRight(uint8_t b);
void changeDir();

#endif /* MotorPWM_H */