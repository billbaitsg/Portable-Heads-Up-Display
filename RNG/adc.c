/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Range Finder 

	Module:	Analog to Digital converter Functions
	
	Desc.:	This file contains the source code for the 
			ADC functions
**********************************************************/

#include "proj_hdr.h"

/* Initialize ADC functionality */
void adc_init(void)
{
	ADMUX |= (0<<REFS1) | (0<<REFS0);	/* Vcc used as Vref, disconnect from PB0 */
	ADMUX |= (1<<ADLAR);				/* ADC Left Adjust Result */
	ADMUX |= 2;							/* Single Ended Input ADC2 selected */
	ADCSRA |= (1<<ADEN);				/* ADC Enabled */
	ADCSRA |= (1<<ADIE);				/* ADC Interrupt Enabled */
	ADCSRA |= 3;						/* 8MHz Clk/64 = 125kHz, ADC Prescaler */
	
	ADC_START;	/* Start ADC Conversion */
}

/* ADC finished conversion interrupt */
ISR(ADC_vect)
{
	RANGE = ADCH;	/* Read ADC value into Range variable */
	ADC_START;	/* Start next ADC conversion */
}