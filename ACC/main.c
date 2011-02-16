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
		if( !USI_SS )	/* if this SPI slave is selected */
		{
			if( cmd == 'X' )	/* if the X axis is requested */
			{
				USI_SPI_putc(X_AXIS);	/* Send X-axis value */
				USI_SPI_wait();			/* wait for transmission to finish */
			}
			else if( cmd == 'Y' )	/* if the Y axis is requested */
			{
				USI_SPI_putc(Y_AXIS);	/* Send Y-axis value */
				USI_SPI_wait();			/* wait for transmission to finish */
			}
			else if( cmd == 'Z' )	/* if the Z axis is requested */
			{
				USI_SPI_putc(Z_AXIS);	/* Send X-axis value */
				USI_SPI_wait();			/* wait for transmission to finish */
			}
			else{}	/* all other requests, do nothing */
		}
		else{}	/* if not selected, do nothing */
	}/* End of while */
	return 0;
}/* End of main */