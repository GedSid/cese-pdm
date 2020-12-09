/*
 * semaphore.h
 *
 *  Created on: Nov 4, 2020
 *      Author: ju
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_


#include "sapi.h"

typedef struct{
	uartMap_t uart;
	uint32_t baudrate;
	char buffer[32];
} uart_t;

void communicationConfig( uart_t * myUart, uartMap_t uart, uint32_t baudrate );

void uartSend( uart_t * myUart, double measure_c, bool_t unit );

#endif /* COMMUNICATION_H_ */
