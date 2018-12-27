/*
 * lenkung.c
 *
 * Created: 10.05.2018 19:09:40
 *  Author: Kenan
 */ 
#include "lenkung.h"

uint16_t PWM_width_lenkung = 2000;

void initLenkungPwm(){
	ICR4 = PWM_width_lenkung;
	OCR4A = 2000;
	OCR4B = 2000;
	TCCR4A = (1<<COM4A1)|(1<<COM4B1)|(1<<WGM41);
	TCCR4B = (1<<WGM43)|(1<<CS41)|(1<<WGM43);
	DDRH = (1<<PH3)|(1<<PH4)|(1<<PH5);
}
 int speedo = 1500;
 int wohin = 1;

void changeLenkung(){
	if(wohin == 1){
		OCR4A = 0;
		OCR4B = 0;
	}
	if(wohin == 0){
		OCR4A = speedo;
		OCR4B = 0;
	}
	if(wohin == 2){
		OCR4A = 0;
		OCR4B = speedo;
	}
}