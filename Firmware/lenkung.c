/*
 * lenkung.c
 *
 * Created: 10.05.2018 19:09:40
 *  Author: Kenan Kajkus
 */ 
#include "lenkung.h"
#include "UartMessage.h"
uint16_t PWM_width_lenkung = 2000;

UartMessage * m_message;

void initLenkungPwm(UartMessage * message)
{
	m_message = message;
	ICR4 = PWM_width_lenkung;
	OCR4A = 2000;
	OCR4B = 2000;
	TCCR4A = (1<<COM4A1)|(1<<COM4B1)|(1<<WGM41);
	TCCR4B = (1<<WGM43)|(1<<CS41)|(1<<WGM43);
	DDRH = (1<<PH3)|(1<<PH4)|(1<<PH5);
}
 int speedo = 1500;
 int speedofast = 2000; 
 int idleOffset = 10;
 int wohin = 1;

//0..63 left fast 
//64..127 left
//128..191 right
//192..255 right fast
void changeLenkung(){
	uint8_t stickPosition = getJoystickX(m_message);
	
	if( stickPosition <= 127 - idleOffset){
		if (stickPosition <= 63 - idleOffset/2)
		{
			OCR4A = speedofast;
			OCR4B = 0;
		}else
		{
			OCR4A = speedo;
			OCR4B = 0;
		}
		return;
	}

	if ( stickPosition > 127 + idleOffset)
	{
		if (stickPosition > 191 + idleOffset/2)
		{
			OCR4A = 0;
			OCR4B = speedofast;
		}else
		{
			OCR4A = 0;
			OCR4B = speedo;
		}
		return;
	}
	
	//default should be no steering
	OCR4A = 0;
	OCR4B = 0;
}