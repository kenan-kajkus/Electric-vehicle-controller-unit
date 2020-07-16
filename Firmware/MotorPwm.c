/*
 * MotorPwm.c
 *
 * Created: 23.04.2018 08:09:42
 *  Author: Kenan Kajkus
 */ 
#include "MotorPwm.h"
#include "timer.h"

UartMessage * message;
//2000 represents 0% motorpower
uint16_t PWM_width_motor = 2000;
int motor_speed = 0;

void initMotordriver(UartMessage * uartMessage){
	message = uartMessage;
	DDRA |=  (1<<PINA5)|(1<<PINA1);// direction pins l/r set to output
	DDRC |= (1<<PINC0)|(1<<PINC4);// direction pins L/R set to output
	PORTA |= (1<<PINA5)|(1<<PINA1);
	PORTC |= (1<<PINC0)|(1<<PINC4);
	//_delay_ms(5000);
	PORTA &= ~(1<<PINA1);
	PORTC &= ~(1<<PINC4);
}

void initPwmMotor(){
	ICR3 = PWM_width_motor;
	OCR3A = PWM_width_motor;
	OCR3C = PWM_width_motor;
	TCCR3A|= (1<<COM3A1)|(1<<COM3C1)|(1<<WGM31);
	TCCR3B|= (1<<WGM33)|(1<<CS31)|(1<<WGM33);
	DDRE |= MOTOR_LEFT_PWM|MOTOR_RIGHT_PWM;
}

void changeSpeed(){
	static unsigned long lasttime = 0;
	static int lastSpeed = 0;
	if(lasttime + 50 > millis()){
		return ;
	}
	uint8_t brakeVal = getMagSensor(message);
	uint8_t stickVal = getJoystickY(message);
	int tempSpeed;

	if(stickVal > 128+10 && motor_speed < 255)
	{
		motor_speed = motor_speed + 5;
	}
	if (stickVal<=127-10 && motor_speed >= -255)
	{
		motor_speed = motor_speed - 5;
	}

	if(motor_speed < 0)
	{
		tempSpeed = -motor_speed;
		if (lastSpeed > 0)
		{
			setBackward();
		}
	}
	else
	{
		tempSpeed = motor_speed;
		if (lastSpeed <= 0)
		{
			setForward();
		}
	}

	uint8_t target_speed;
	if (brakeVal>=tempSpeed)
	{
		target_speed = 0;
	}
	else
	{
		target_speed = map(tempSpeed-brakeVal);
	}
	
	changeSpeedLeft(PWM_width_motor-target_speed);
	changeSpeedRight(PWM_width_motor-target_speed);

	lastSpeed = motor_speed;
	lasttime = millis();
}

void changeSpeedLeft(long percentLeft){
	OCR3A = percentLeft;
}

void changeSpeedRight(long percentRight){
	OCR3C = percentRight;
}

void setForward()
{
	PORTA |= (1<<PINA5)|(1<<PINA1);
	PORTC |= (1<<PINC0)|(1<<PINC4);
	_delay_ms(10);
	PORTA &= ~(1<<PINA1);
	PORTC &= ~(1<<PINC4);
}

void setBackward()
{
	PORTA |= (1<<PINA5)|(1<<PINA1);
	PORTC |= (1<<PINC0)|(1<<PINC4);
	_delay_ms(10);
	PORTA &= ~(1<<PINA5);
	PORTC &= ~(1<<PINC0);
}

long map(uint8_t x)
{
	long in_min = 0;
	long in_max = 255;
	long out_min = 0;
	long out_max = 2000;
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}