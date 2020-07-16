/*
 * Bollerwagen.c
 *
 * Created: 29.03.2018 23:38:35
 * Author : Kenan
 */ 
#include "bollerwagen.h"
#include "emergencyStop.h"
#include "MotorPwm.h"
#include "lenkung.h"
#include <avr/io.h>
#include "uart.h"
#include <avr/interrupt.h>
#include "UartMessage.h"
#include "messageReader.h"
#include "timer.h"

#define BAUTRATE 9600
#include "Watchdog.h"
char message[20];

void setup(){
	startEmergencyStop();
	startTimer();
	uart_init(UART_BAUD_SELECT(BAUTRATE,F_CPU));
	initMotordriver(uartMessage);
	initPwmMotor();
	initLenkungPwm(uartMessage);
	watchdog_init();
}

int main(void)
{	
	setup();
	//set interrupts
	sei();
	while (1) 
	{
		watchdog_reset();
		uart_gets(message,20);
		parseMessage(message,0);
		changeSpeed();
		changeLenkung();
    }
}
