/*
 * main.c
 *
 *  Created on: Nov 4, 2020
 *      Author: ju
 */
#include "sapi.h"
#include "hydroFSM.h"
#include "measurement.h"
#include "communication.h"


int main( void ){

	uart_t my_uart;
	delay_t delay;
	hydro_state_t st_hydro_calc = STATE_IDLE;
	// ----- Setup -----------------------------------
	measurementeConfig();
	communicationConfig( & my_uart, UART_USB, 115200 );

	// ----- Repeat for ever -------------------------
	while( TRUE ) {
			hydroCalcFEM( & my_uart, & st_hydro_calc, & delay );
	}

	// YOU NEVER REACH HERE, because this program runs directly or on a
	// microcontroller and is not called by any Operating System, as in the
	// case of a PC program.
	return 0;
}
