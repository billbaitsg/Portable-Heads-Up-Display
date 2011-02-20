/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Display Controller
	
	Module:	Main program
	
	Desc.:	This is the main program section of the 
			Display microcontroller
**********************************************************/

#include "proj_hdr.h"	/* Include project header file */

/* Calculation for UART baud rate */
#define FOSC 8000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

/* Global Variables */
volatile unsigned char X_AXIS = 0;	/* X-axis acceleration */
volatile unsigned char Y_AXIS = 0;	/* Y-axis acceleration */
volatile unsigned char Z_AXIS = 0;	/* Z-axis acceleration */
volatile unsigned char RANGE = 0;	/* Range finder distance */
volatile unsigned char LIGHT = 0;	/* Ambient light level */
volatile int ALTITUDE = 0;			/* Altitude in meters */
volatile unsigned int SPEED = 0;	/* Speed in kilometers per hour */
volatile unsigned char HEADING = 0;	/* Heading of the vehicle */

int main(void)
{
	/* Local Variables */
	unsigned char cmd = 0;
	
	/* Initialize software modules */
	UART_init(MYUBRR);	/* Initialize UART */
	SPI_SlaveInit();	/* Initialize SPI */
	
	sei();	/* Enable global interrupts */
	
	while(1)
	{
		if( !SPI_SS )	/* SPI slave selected */
		{
			SPI_SSn(0);		/* Active low slave selected */
			cmd = SPI_getc();
			if( cmd == 'L' )	/* if the X axis is requested */
			{
				SPI_putc(LIGHT);	// Send temp value to SPI and increment
				SPI_wait();		// wait for transmission to finish
			}
			else{}	/* all other requests, do nothing */
		}
		else	/* SPI slave not selected */
		{
			SPI_SSn(1);		/* Active low slave not selected */
		}/* End of if */
	}	/* End of while */
	return 0;
}	/* End of main */