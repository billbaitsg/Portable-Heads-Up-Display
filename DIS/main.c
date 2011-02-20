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
	unsigned char cmd = 120;
	unsigned char hbyte = 0;
	unsigned char lbyte = 0;
	
	/* Initialize software modules */
	UART_init(MYUBRR);	/* Initialize UART */
	SPI_SlaveInit();	/* Initialize SPI */
	
	sei();	/* Enable global interrupts */
	while(1)
	{
		cmd = SPI_getc();
		SPI_putc( cmd + 5 );
		// if( !SPI_SS )	/* SPI slave selected */
		// {
			// SPI_SSn(0);		/* Active low slave selected */
			// cmd = SPI_getc();
			// if( cmd == 'x' )	/* if the X-axis is sent */
			// {
				// X_AXIS = SPI_getc();	/* Get X-axis value from the Main Controller */
			// }
			// else if( cmd == 'y' )	/* if the Y-axis is sent */
			// {
				// Y_AXIS = SPI_getc();	/* Get Y-axis value from the Main Controller */
			// }
			// else if( cmd == 'z' )	/* if the Z-axis is sent */
			// {
				// Z_AXIS = SPI_getc();	/* Get Z-axis value from the Main Controller */
			// }
			// else if( cmd == 'l' )	/* if the Ambient Light level is sent */
			// {
				// LIGHT = SPI_getc();		/* Get Ambient Light value from the Main Controller */
			// }
			// else if( cmd == 'r' )	/* if the Range distance is sent */
			// {
				// RANGE = SPI_getc();	/* Get Range value from the Main Controller */
			// }
			// else if( cmd == 'a' )	/* if the Altitude is sent */
			// {
				// hbyte = SPI_getc();	/* Get Altitude high byte value from the Main Controller */
				// lbyte = SPI_getc();	/* Get Altitude low byte value from the Main Controller */
				// ALTITUDE = (hbyte<<8) & lbyte;	/* Combine high and low bytes for the Altitude */
			// }
			// else if( cmd == 'v' )	/* if the Speed is sent */
			// {
				// hbyte = SPI_getc();	/* Get Speed high byte value from the Main Controller */
				// lbyte = SPI_getc();	/* Get Speed low byte value from the Main Controller */
				// SPEED = (hbyte<<8) & lbyte;	/* Combine high and low bytes for the Speed */
			// }
			// else if( cmd == 'b' )	/* if the Bearing is sent */
			// {
				// hbyte = SPI_getc();	/* Get Bearing high byte value from the Main Controller */
				// lbyte = SPI_getc();	/* Get Bearing low byte value from the Main Controller */
				// BEARING = (hbyte<<8) & lbyte;	/* Combine high and low bytes for the Bearing */
			// }
			// else if( cmd == 'h' )	/* if the Hours are sent */
			// {
				// HOURS = SPI_getc();	/* Get Hours value from the Main Controller */
			// }
			// else if( cmd == 'm' )	/* if the Minutes are sent */
			// {
				// MINUTES = SPI_getc();	/* Get Minutes value from the Main Controller */
			// }
			// else if( cmd == 's' )	/* if the Hours are sent */
			// {
				// SECONDS = SPI_getc();	/* Get Seconds value from the Main Controller */
			// }
			// else{}	/* all other requests, do nothing */
		// }
		// else	/* SPI slave not selected */
		// {
			// SPI_SSn(1);		/* Active low slave not selected */
		// }/* End of if */
	}	/* End of while */
	return 0;
}	/* End of main */