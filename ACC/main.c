/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Accelerometer Microcontroller
	
	Module:	Main program
	
	Desc.:	This is the main program section of the 
			Accelerometer microcontroller
**********************************************************/

#include "proj_hdr.h"	/* Include project header file */

/* Global Variables for ADC readings */
volatile char X_AXIS = 10;	/* X-axis accelerometer reading */
volatile char Y_AXIS = 20;	/* Y-axis accelerometer reading */
volatile char Z_AXIS = 30;	/* Z-axis accelerometer reading */

int main(void)
{	
	/* Initialize software modules */
	adc_init();	/* Initialize ADC */
	//USI_SPI_initmaster();
	USI_SPI_initslave();	/* Initialize SPI as slave */
	
	sei();	/* Enable global interrupts */
	
	while(1)
	{
		
	}/* End of while */
	return 0;
}/* End of main */