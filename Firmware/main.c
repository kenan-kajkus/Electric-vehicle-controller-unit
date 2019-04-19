/*
 * Bollerwagen.c
 *
 * Created: 29.03.2018 23:38:35
 * Author : Kenan
 */ 
#include "bollerwagen.h"
#include "MotorPwm.h"
#include "lenkung.h"
#include <avr/io.h>
#include "uart.h"
#include <avr/interrupt.h>

#define BAUTRATE 38400UL
#include "Watchdog.h"
char message[20];
struct UART_message{
	int dir;
	int speedRight;
	int speedLeft;
	} uart_m;
Motors m;

ISR (TIMER1_OVF_vect)
{
	/* Interrupt Aktion alle 2Hz*/
	TCNT1 = 0x7a11;
	
	if(!(PINL & (1<<PL0))&&((PINL & (1<<PL2)))){
		return;		
	}else{
		cli();
		wdt_enable (WDTO_15MS);
		while (1);
	}
}
void setup(){
	DDRL &=!((1<<PL0)|(1<<PL2));
	PORTL |= ((1<<PL0)|(1<<PL2));
	m.speedLeft=0;
	m.speedRight=0;
	// Timer 1 konfigurieren
	TCCR1A = 0; // zur Sicherheit alles auf 0 setzen
	TCCR1B = 0; // zur Sicherheit alles auf 0 setzen

	TCNT1 = 0x7a11;        // Timer nach obiger Rechnung vorbelegen
	TCCR1B |= (1<< CS12);    // 256 als Prescale-Wert
	TIMSK1 |= (1 << TOIE1);   // Timer Overflow Interrupt aktivieren
	DDRF |= (1<<PINF0);
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
	
	while (nextChar != '\n' &&StringLength < MaxLength-1 )
	{
		*Buffer++ = nextChar;
		StringLength++;
		nextChar = uart_getc_wait();
	}
	*Buffer = '\0';
}
void readUART(){
	int dir = (int)message[0]-48;
	if(dir!=uart_m.dir){
		uart_m.dir = dir;
	}
	//-48 for asci shift
	int speed100= (int)message[2]-48;
	int speed10= (int)message[3]-48;
	int speed1= (int)message[4]-48;
	uart_m.speedLeft = speed100*100+speed10*10+speed1;
	uart_m.speedRight = speed100*100+speed10*10+speed1;
	wohin = (int)message[6]-48;
	
}
void startupCheck(){
	do
	{
		uart_gets(message,20);
		readUART();
	} while (m.speedLeft!=0);
	
}
int main(void)
{	
	setup();
	uart_init(UART_BAUD_SELECT(9600,16000000UL));
	//set interrupts
	sei();
	initMotordriver();
	m.speedLeft = 0;
	m.speedRight = 0;
	m.dir=1;
	initPwmMotor();
	initLenkungPwm();
	startupCheck();
	watchdog_init();
	while (1) 
	{
		watchdog_reset();
		uart_gets(message,20);
		readUART();
		changeDir(uart_m.dir);
		changeSpeed(uart_m.speedLeft,uart_m.speedRight);
		changeLenkung();
    }
}
