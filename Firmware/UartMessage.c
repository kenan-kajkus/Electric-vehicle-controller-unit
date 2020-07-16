/*
 * UartMessage.c
 *
 * Created: 09.07.2020 15:44:26
 *  Author: Kenan Kajkus
 */ 
 
 #include "UartMessage.h"

 struct UartMessage
 {
	 uint8_t magnet;
	 uint8_t joystick_X;
	 uint8_t joystick_Y;
	 uint8_t buttons;
	 uint8_t newValue;
 };

 void setUartMessage(UartMessage * uartMessage, uint8_t magVal, uint8_t stickXVal, uint8_t stickYVal)
 {
	uartMessage->newValue = 1;
	uartMessage->magnet = magVal;
	uartMessage->joystick_X = stickXVal;
	uartMessage->joystick_Y = stickYVal;
 }

 uint8_t getJoystickX(UartMessage * uartMessage)
 {
	return uartMessage->joystick_X;
 }

 uint8_t getJoystickY(UartMessage * uartMessage)
 {
	 return uartMessage->joystick_Y;
 }

 
 uint8_t getMagSensor(UartMessage * uartMessage)
 {
	return uartMessage->magnet;
 }

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

