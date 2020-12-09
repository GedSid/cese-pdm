/*
 * semaphore.h
 *
 *  Created on: Nov 4, 2020
 *      Author: ju
 */

#ifndef MEASUREMENT_H_
#define MEASUREMENT_H_


#include "sapi.h"

void measurementeConfig( void );

uint16_t measurement( void );

double convert2Celcius( uint16_t measure_adc );

double convert2Fareheit( uint16_t measure_adc );

#endif /* MEASUREMENT_H_ */
