/*
 * messageParser.h
 *
 * Created: 10.07.2020 09:08:04
 *  Author: Kenan Kajkus
 */ 


#ifndef MESSAGEPARSER_H_
#define MESSAGEPARSER_H_

#include "UartMessage.h"

UartMessage * uartMessage;

void parseMessage(char * rawData, int rawDataLength);
int unreadUartMessage();
UartMessage * getUartMessage();
#endif /* MESSAGEPARSER_H_ */