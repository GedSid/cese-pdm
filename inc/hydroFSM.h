/*
 * semaphore.h
 *
 *  Created on: Nov 4, 2020
 *      Author: ju
 */

#ifndef HYDRO_FSM_H_
#define HYDRO_FSM_H_

#include "communication.h"

typedef enum{
	STATE_IDLE = 0,
	STATE_MEASURE = 1,
	STATE_CONVERTION = 2,
	STATE_COMMUNICATION = 3
} hydro_state_t;

void hydroCalcFEM( uart_t * my_uart, hydro_state_t * st_hydro_calc, delay_t * delay );

void led_on (gpioMap_t pin);

void led_off (gpioMap_t pin);

#endif /* HYDRO_FSM_H_ */
