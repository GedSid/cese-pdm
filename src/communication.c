/*=============================================================================
 *  * main.c
 *
 *  Created on: Nov 4, 2020
 *      Author: ju
 * Date: 2019/05/03
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "sapi.h"
#include "communication.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/


/*----------------- declaracion de funcion de configuracion ----------------*/

void communicationConfig( uart_t * myUart, uartMap_t uart, uint32_t baudrate ){
	// Se inisializa la interfaz UART
	myUart->uart = uart;
	myUart->baudrate = baudrate;
	uartConfig( myUart->uart, myUart->baudrate );
}

/*----------------- declaracion de funciones de comunicacion ----------------*/

void uartSend( uart_t * myUart, double measure_c, bool_t unit ){
    // Se convierte la medicion y sel a manda por UART
	sprintf(myUart->buffer, "%f", measure_c);
    uartWriteString( myUart->uart, "La temperatura es " );
    uartWriteString( myUart->uart, myUart->buffer );
    if (1 == unit){
    	uartWriteString( myUart->uart, " C" );
    } else{
    	uartWriteString( myUart->uart, " F" );
    }
    uartWriteString( myUart->uart, " \r\n" );
}
