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

struct UartMessage;

typedef struct UartMessage UartMessage;

UartMessage InitMessage();

uint8_t buttonState(UartMessage * uartMessage, uint8_t button);

void setUartMessage(UartMessage * uartMessage, uint8_t magVal, uint8_t stickXVal, uint8_t stickYVal);

uint8_t getJoystickX(UartMessage * uartMessage);

uint8_t getJoystickY(UartMessage * uartMessage);

uint8_t getMagSensor(UartMessage * UartMessage);

void setButtonState(UartMessage * uartMessage, uint8_t button);

void clearButtonState(UartMessage * uartMessage, uint8_t button);
#endif /* UARTMESSAGE_H_ */