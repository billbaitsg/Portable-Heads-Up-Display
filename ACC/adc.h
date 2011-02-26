/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Accelerometer Microcontroller

	Module:	Analog to Digital converter header
	
	Desc.:	This file contains the function prototypes and
			variable definitions for the ADC functions
**********************************************************/
#ifndef ADC_H
#define ADC_H
	/* ADC function prototypes */
	void adc_init(void);	/* Initialize ADC functionality */
	ISR(ADC_vect);	/* ADC finished conversion interrupt */
	
	/* ADC Macros */
	#define ADC_START (ADCSRA |= (1<<ADSC))
#endif
