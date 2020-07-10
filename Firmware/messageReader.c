/*
 * messageParser.c
 *
 * Created: 10.07.2020 09:07:33
 *  Author: Kenan Kajkus
 */ 
 #include <stdio.h>
 #include "messageReader.h"

 int newMessage;

 void parseMessage(char * rawData, int rawDataLength)
 {
	uint8_t magVal, stickXVal, stickYVal;
	if (sscanf(rawData,"M%hhu\tX%hhu\tY%hhu", &magVal, &stickXVal, &stickYVal) == 3)
	{
		setUartMessage(uartMessage, magVal, stickXVal, stickYVal);
		newMessage = 1;
	}
 }

 int unreadUartMessage()
 {
	return newMessage;
 }
