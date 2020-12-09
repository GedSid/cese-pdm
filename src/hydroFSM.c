/*=============================================================================
 *  * main.c
 *
 *  Created on: Nov 4, 2020
 *      Author: ju
 * Version: 1
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include <string.h>
#include "sapi.h"
#include "hydroFSM.h"
#include "measurement.h"
#include "communication.h"

/*=====[Definition macros of private constants]==============================*/

#define HYDRODELAY     100

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

/*=====[Main function, program entry point after power on or reset]==========*/

bool_t hydroCheckButtons(bool_t * tempUnit);

void hydroCalcFEM(uart_t * my_uart, hydro_state_t * st_hydro_calc, delay_t * delay) {

	bool_t temp_unit;
	bool_t new_button;
	uint16_t adc_measure = 0;
	double temp_measure = 0;
	delayConfig(delay, HYDRODELAY);

	led_on(LED3);

	if (delayRead(delay)) {
		switch (*st_hydro_calc) {
		case STATE_IDLE:
			led_off(LED3);
			led_on(LED1);
			// se espera algun boton
			new_button = hydroCheckButtons(&temp_unit);
			if (TRUE == new_button) {
				*st_hydro_calc = STATE_MEASURE;
			}
			break;
		case STATE_MEASURE:
			led_off(LED1);
			led_on(LED2);
			// se llama al ADC para que haga la medicion
			adc_measure = measurement();
			*st_hydro_calc = STATE_CONVERTION;
			break;
		case STATE_CONVERTION:
			led_off(LED2);
			// aca podria hacer otra maquina de estados que en funcion de la unidad defina calcula la conversion
			if (1 == temp_unit) { // C
				led_on(LEDB);
				temp_measure = convert2Celcius(adc_measure);
				*st_hydro_calc = STATE_COMMUNICATION;
			} else if (0 == temp_unit) { // F
				led_on(LEDR);
				temp_measure = convert2Fareheit(adc_measure);
				*st_hydro_calc = STATE_COMMUNICATION;
			} else {
				*st_hydro_calc = STATE_IDLE;
			}
			break;
		case STATE_COMMUNICATION:
			led_off(LEDR);
			led_off(LEDB);
			led_on(LEDG);
			// se envian los datos por UART
			uartSend(my_uart, temp_measure, temp_unit);
			*st_hydro_calc = STATE_IDLE;
			break;
		default:
			*st_hydro_calc = STATE_IDLE;
		}
		delayWrite(delay, HYDRODELAY);
	}
}

bool_t hydroCheckButtons(bool_t * tempUnit) {
	if (!gpioRead(TEC1)) {
		*tempUnit = 1;
		return 1;
	} else if (!gpioRead(TEC2)) {
		*tempUnit = 0;
		return 1;
	} else {
		return 0;
	}
}

// Funciones para prender y apagar cualquier LED

void led_on(gpioMap_t pin) {
	bool_t status;
	status = gpioWrite(pin, ON);
}

void led_off(gpioMap_t pin) {
	bool_t status;
	status = gpioWrite(pin, OFF);
}
