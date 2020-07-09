/*
 * UartMessage.c
 *
 * Created: 09.07.2020 15:44:26
 *  Author: Kenan Kajkus
 */ 
 
 #include "UartMessage.h"

 uint8_t buttonState(UartMessage * uartMessage, uint8_t button)
 {
	 return uartMessage->buttons & button;
 }

 void setButtonState(UartMessage * uartMessage, uint8_t button)
 {
	uartMessage->buttons |= button;
 }

 void clearButtonState(UartMessage * uartMessage, uint8_t button)
 {
	uartMessage->buttons &= ~button;
 }

