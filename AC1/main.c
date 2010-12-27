/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Accelerometer Microcontroller 1
	
	Module:	Main program
	
	Desc.:	This is the main program section of the 
			accelerometer microcontroller 1
**********************************************************/

#include "proj_hdr.h"	/* Include project header file */

int main(void)
{
	/* Local Variables */
	unsigned char val = 0;
	
	/* Initialize software modules */
	//adc_init();	/* Initialize ADC */
	USI_SPI_initmaster();	/* Initialize SPI as master */
	
	while(1)
	{
		USI_SPI_put( val++ );	// Send temp value to SPI and increment
		USI_SPI_wait();		// wait for transmission to finish
		_delay_ms(100);
	}	/* End of while */
	return 0;
}	/* End of main */