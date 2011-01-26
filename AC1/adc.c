/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Accelerometer Microcontroller 1 

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
	if( (ADMUX & 0x0F) == 2 )	/* if ADC2 is selected */
	{
		X_AXIS = ADCH;	/* Read the X-axis accelerometer measurment */
		ADMUX = (ADMUX & ~0x0F) | 3;	/* switch to ADC3 */
	}
	else
	{
		Y_AXIS = ADCH;	/* Read the Y-axis accelerometer measurment */
		ADMUX = (ADMUX & ~0x0F) | 2;	/* switch back to ADC2 */
	}
	ADC_START;	/* Start next ADC conversion */
}