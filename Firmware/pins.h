/*
 * pins.h
 *
 * Created: 12.04.2018 13:57:51
 *  Author: Kenan
 */ 


#ifndef PINS_H_
#define PINS_H_
#include <avr/io.h>
#include <stdint.h>
extern uint8_t MOTOR_LEFT_PWM;
#define MOTOR_LEFT_HIB
#define MOTOR_LEFT_FOR
#define MOTOR_LEFT_BACK

#define MOTOR_RIGHT_PWM (1<<PE3)
#define MOTOR_RIGHT_FOR
#define MOTOR_RIGHT_BACK


#endif /* PINS_H_ */