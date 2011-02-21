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
volatile unsigned char BEARING = 0;	/* Heading of the vehicle */
volatile unsigned char HOURS = 12;	/* Hour of the current time */
volatile unsigned char MINUTES = 0;	/* Minutes of the current hour */
volatile unsigned char SECONDS = 0;	/* Seconds of the current hour */

int main(void)
{
	/* Local Variables */
	
	/* Initialize software modules */
	SPI_SlaveInit();	/* Initialize SPI */
	UART_init(MYUBRR);	/* Initialize UART */
	
	sei();	/* Enable global interrupts */
	while(1)
	{
		UART_putc(X_AXIS);
		_delay_ms(500);
	}	/* End of while */
	return 0;
}	/* End of main */