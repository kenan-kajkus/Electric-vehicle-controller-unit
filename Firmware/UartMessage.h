/*
 * UartMessage.h
 *
 * Created: 09.07.2020 15:07:14
 *  Author: Kenan Kajkus
 */ 


#ifndef UARTMESSAGE_H_
#define UARTMESSAGE_H_

#include <stdint-gcc.h>

#define TRIGGER_BUTTON 0x01
#define JOYSTICK_BUTTON 0x02
#define A_BUTTON 0x04
#define B_BUTTON 0x08
#define BOOL5 0x10
#define BOOL6 0x20
#define BOOL7 0x40
#define BOOL8 0x80

struct UartMessage
{
	uint8_t magnet;
	uint8_t joystick_X;
	uint8_t joystick_Y;
	uint8_t buttons;
};
typedef struct UartMessage UartMessage;

uint8_t buttonState(UartMessage * uartMessage, uint8_t button);

void setButtonState(UartMessage * uartMessage, uint8_t button);

void clearButtonState(UartMessage * uartMessage, uint8_t button);
#endif /* UARTMESSAGE_H_ */