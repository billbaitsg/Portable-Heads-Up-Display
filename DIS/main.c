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
volatile unsigned char X_AXIS = 100;	/* X-axis acceleration */
volatile unsigned char Y_AXIS = 128;	/* Y-axis acceleration */
volatile unsigned char Z_AXIS = 156;	/* Z-axis acceleration */
volatile unsigned char RANGE = 10;	/* Range finder distance */
volatile unsigned char LIGHT = 10;	/* Ambient light level */
volatile int ALTITUDE = 12345;			/* Altitude in meters */
volatile unsigned int SPEED = 1234;	/* Speed in kilometers per hour */
volatile unsigned char BEARING = 123;	/* Heading of the vehicle */
volatile unsigned char HOURS = 12;	/* Hour of the current time */
volatile unsigned char MINUTES = 34;	/* Minutes of the current hour */
volatile unsigned char SECONDS = 56;	/* Seconds of the current hour */

int main(void)
{
	/* Local Variables */
	unsigned char cmd = 0x20;
	
	/* Initialize software modules */
	SPI_SlaveInit();	/* Initialize SPI */
	UART_init(MYUBRR);	/* Initialize UART */
	
	sei();	/* Enable global interrupts */

	_delay_ms(200);
	reset();
	/* Wait 200ms for display to boot up */
	_delay_ms(500);

	while(1)
	{
		cursor_home();
		display_counter();
		//cursor_position(0,0);	/* Set cursor row 0, column 0 */
		cursor_home();
		UART_puts("\tAccelerometer");	/* Print information */
		display_x();	/* Display X-axis value */
		display_y();	/* Display Y-axis value */
		display_z();	/* Display Z-axis value */
		UART_puts("\n\r\tRange Finder");
		display_r();	/* Display Range value */
		UART_puts("\n\r\tAmbient Light");
		display_l();	/* Display Ambient Light value */
		cursor_home();
		UART_puts("\t\t\tGPS Data");
		display_a();
		display_v();
		display_b();
		UART_puts("\n\n\r\t\t\tGPS Time");
		display_time();
		_delay_ms(100);
	}	/* End of while */
	return 0;
}	/* End of main */
