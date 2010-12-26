/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Accelerometer Microcontroller 1

	Module:	Analog to Digital converter header
	
	Desc.:	This file contains the function prototypes and
			variable definitions for the ADC functions
**********************************************************/

#include "proj_hdr.h"

volatile char ADC_READING = 0;	/* Variable to store ADC reading */

/* Initialize ADC functionality */
void adc_init(void)
{
	
}

/* ADC finished conversion interrupt */
ISR(ADC_vect)
{
	
}