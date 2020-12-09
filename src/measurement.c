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
#include "measurement.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Definitions of extern global variables]==============================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

const double ADC2CELCIUSMULTI = 100/1024;
const double ADC2FAREHEITMULTI = ADC2CELCIUSMULTI*9/5;
const double ADC2FAREHEITOFFSET = 32;

/*=====[Main function, program entry point after power on or reset]==========*/


/*----------------- declaracion de funcion de configuracion ----------------*/

void measurementeConfig( void ){
	// Se inicializa la CIAA
	boardInit();
	// Se habilita el ADC
	adcConfig( ADC_ENABLE ); // Parametros: ADC_ENABLE,  ADC_DISABLE
}

/*----------------- declaracion de funcion de medicion ----------------*/

uint16_t measurement( void ){
	uint16_t measure_adc;
	measure_adc = (uint16_t) adcRead( CH1 );
	return measure_adc;
}

double convert2Celcius( uint16_t measure_adc ){
	// El ADC mide entre 0 y 1024, se supone una temperatura entre 0 y 100 grados,
	// por ser agua.
	double measure_c;
	measure_c = (double) measure_adc;
	measure_c = ADC2CELCIUSMULTI * measure_c;
	return measure_c;
}

/*----------------- declaracion de funciones de conversion ----------------*/

double convert2Fareheit( uint16_t measure_adc ){
	// El ADC mide entre 0 y 1024, se supone una temperatura entre 0 y 100 grados,
	// por ser agua.
	double measure_c;
	measure_c = (double) measure_adc;
	measure_c = (ADC2FAREHEITMULTI * measure_c) + ADC2FAREHEITOFFSET;
	return measure_c;
}
