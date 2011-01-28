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

/* Global Variables for ADC readings */
volatile char X_AXIS = 0;	/* X-axis accelerometer reading */
volatile char Y_AXIS = 0;	/* Y-axis accelerometer reading */
volatile char Z_AXIS = 0;	/* Z-axis accelerometer reading */

int main(void)
{
	/* Local Variables */
	unsigned char cmd = 0;
	
	/* Initialize software modules */
	adc_init();	/* Initialize ADC */
	//USI_SPI_initmaster();
	USI_SPI_initslave();	/* Initialize SPI as slave */
	
	sei();	/* Enable global interrupts */
	
	while(1)
	{
		cmd = USI_SPI_getc();
		if( cmd == 'X' )	/* if the X axis is requested */
		{
			USI_SPI_putc(X_AXIS);	/* Send X-axis value */
			USI_SPI_wait();			/* wait for transmission to finish */
		}
		else if( cmd == 'Y' )	/* if the Y axis is requested */
		{
			USI_SPI_putc(X_AXIS);	/* Send Y-axis value */
			USI_SPI_wait();			/* wait for transmission to finish */
		}
		else if( cmd == 'Z' )	/* if the Z axis is requested */
		{
			USI_SPI_putc(Z_AXIS);	/* Send X-axis value */
			USI_SPI_wait();			/* wait for transmission to finish */
		}
		else	/* all other requests, do nothing */
		{
			/* Do nothing */
		}/* End of if */
	}/* End of while */
	return 0;
}/* End of main */