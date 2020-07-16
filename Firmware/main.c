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

#define BAUTRATE 38400UL
#include "Watchdog.h"
char message[20];

void setup(){
	startEmergencyStop();
	startTimer();
	uart_init(UART_BAUD_SELECT(9600,F_CPU));
	initMotordriver(uartMessage);
	initPwmMotor();
	initLenkungPwm(uartMessage);
	watchdog_init();
}

uint8_t uart_getc_wait(){
	unsigned int c;
	do 
	{
		c = uart_getc();
	} while (c == UART_NO_DATA);

	return (uint8_t) c;
}

void uart_gets(char* Buffer, uint8_t MaxLength){
	uint8_t nextChar;
	uint8_t StringLength = 0;
	
	nextChar = uart_getc_wait();
	
	while (nextChar != '\n' && StringLength < MaxLength-1 )
	{
		*Buffer++ = nextChar;
		StringLength++;
		nextChar = uart_getc_wait();
	}
	*Buffer = '\0';
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
