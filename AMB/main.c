/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Ambient Light
	
	Module:	Main program
	
	Desc.:	This is the main program section of the 
			Ambient Light microcontroller
**********************************************************/

#include "proj_hdr.h"	/* Include project header file */

/* Global Variables for ADC readings */
volatile char LIGHT = 0;	/* Ambient Light value */

int main(void)
{
	/* Local Variables */
	unsigned char cmd = 0;
	
	/* Initialize software modules */
	adc_init();				/* Initialize ADC */
	USI_SPI_initslave();	/* Initialize SPI as slave */
	
	sei();	/* Enable global interrupts */
	
	while(1)
	{
		cmd = USI_SPI_getc();
		if( !USI_SS )	/* if this SPI slave is selected */
		{
			if( cmd == 'L' )	/* if the X axis is requested */
			{
				USI_SPI_putc(LIGHT);	// Send temp value to SPI and increment
				USI_SPI_wait();		// wait for transmission to finish
			}
			else{}	/* all other requests, do nothing */
		}
		else	/* if not selected, do nothing */
		{
			/* Do nothing */
		}/* End of if */
	}	/* End of while */
	return 0;
}	/* End of main */