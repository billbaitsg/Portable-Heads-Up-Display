/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Accelerometer Microcontroller

	Module:	Analog to Digital converter Functions
	
	Desc.:	This file contains the source code for the 
			ADC functions
**********************************************************/

#include "proj_hdr.h"

/* Initialize ADC functionality */
void adc_init(void)
{
	ADMUX |= (0<<REFS1) | (0<<REFS0);	/* Vcc used as Vref, disconnect from PB0 */
	ADCSRB |= (1<<ADLAR);				/* ADC Left Adjust Result */
	ADMUX = (ADMUX & ~0x3F) | 0;							/* Single Ended Input ADC0 selected */
	ADCSRA |= (1<<ADEN);				/* ADC Enabled */
	ADCSRA |= (1<<ADIE);				/* ADC Interrupt Enabled */
	ADCSRA |= 3;						/* 8MHz Clk/64 = 125kHz, ADC Prescaler */
	
	ADC_START;	/* Start ADC Conversion */
}

/* ADC finished conversion interrupt */
ISR(ADC_vect)
{
	if( (ADMUX & 0x3F) == 0 )	/* if ADC0 is selected */
	{
		X_AXIS = ADCH;	/* Read the X-axis accelerometer measurment */
		ADMUX = (ADMUX & ~0x3F) | 1;	/* switch to ADC1 */
	}
	else if ( (ADMUX & 0x3F) == 1 )	/* if ADC1 is selected */
	{
		Y_AXIS = ADCH;	/* Read the Y-axis accelerometer measurment */
		ADMUX = (ADMUX & ~0x3F) | 2;	/* switch back to ADC2 */
	}
	else 	/* any other ADC selected */
	{
		Z_AXIS = ADCH;	/* Read the Z-axis accelerometer measurement */
		ADMUX = (ADMUX & ~0x3F) | 0;	/* switch back to ADC0 */
	}
	ADC_START;	/* Start next ADC conversion */
}