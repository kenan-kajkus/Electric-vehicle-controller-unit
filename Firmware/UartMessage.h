/*
 * UartMessage.h
 *
 * Created: 09.07.2020 15:07:14
 *  Author: Kenan Kajkus
 */ 


#ifndef UARTMESSAGE_H_
#define UARTMESSAGE_H_

#define TRIGGER_BUTTON 0x01
#define JOYSTICK_BUTTON 0x02
#define A_BUTTON 0x04
#define B_BUTTON 0x08
#define BOOL5 0x10
#define BOOL6 0x20
#define BOOL7 0x40
#define BOOL8 0x80

/*
	uint8_t buttons;

	// Check TRIGGER_BUTTON
	if ( buttons & TRIGGER_BUTTON)
	// do something

	// Set JOYSTICK_BUTTON
	buttons |= JOYSTICK_BUTTON;

	// Clear A_BUTTON
	buttons &= ~A_BUTTON;
*/

struct UartMessage
{
	uint8_t magnet;
	uint8_t joystick_X;
	uint8_t joystick_Y;
	uint8_t buttons;
};

uint8_t buttonState(UartMessage * uartMessage, uint8_t button)
{
	return uartMessage->buttons & button;
}
#endif /* UARTMESSAGE_H_ */