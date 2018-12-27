/*
 * MotorPwm.c
 *
 * Created: 23.04.2018 08:09:42
 *  Author: Kenan
 */ 
#include "MotorPwm.h"

//2000 represents 0% motorpower
uint16_t PWM_width_motor = 2000;

uint16_t percentToSpeed(uint8_t percent){
	if (percent>95)
	{
		return PWM_width_motor-(PWM_width_motor/100)*97;
	}else{
		return PWM_width_motor-(PWM_width_motor/100)*percent;
	}
}

void initMotordriver(){
	DDRA |=  (1<<PINA5)|(1<<PINA1);// direction pins l/r set to output
	DDRC |= (1<<PINC0)|(1<<PINC4);// direction pins L/R set to output
	PORTA |= (1<<PINA5)|(1<<PINA1);
	PORTC |= (1<<PINC0)|(1<<PINC4);
	//_delay_ms(5000);
	PORTA ^= (1<<PINA1);
	PORTC ^= (1<<PINC4);
}

void initPwmMotor(){
	ICR3 = PWM_width_motor;
	OCR3A = PWM_width_motor;
	OCR3C = PWM_width_motor;
	TCCR3A|= (1<<COM3A1)|(1<<COM3C1)|(1<<WGM31);
	TCCR3B|= (1<<WGM33)|(1<<CS31)|(1<<WGM33);
	DDRE |= MOTOR_LEFT_PWM|MOTOR_RIGHT_PWM;
}

void changeSpeed(uint8_t left, uint8_t right){
	changeSpeedLeft(left);
	changeSpeedRight(right);
}

void changeSpeedLeft(uint8_t percentLeft){
	OCR3A = percentToSpeed(percentLeft);
}

void changeSpeedRight(uint8_t percentRight){
	OCR3C = percentToSpeed(percentRight);
}

void changeDir(){
	int a = PORTA;
	int c = PORTC;
	PORTA |= (1<<PINA5)|(1<<PINA1);
	PORTC |= (1<<PINC0)|(1<<PINC4);
	_delay_ms(10);
	//toggling direction pins
	a ^= (1<<PINA5)|(1<<PINA1);
	c ^= (1<<PINC0)|(1<<PINC4);
	PORTA |= a;
	PORTC |= c;
}