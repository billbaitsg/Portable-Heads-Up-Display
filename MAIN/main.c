/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Main Controller
	
	Module:	Main program
	
	Desc.:	This is the main program section of the 
			Main microcontroller
**********************************************************/

#include "proj_hdr.h"	/* Include project header file */

/* Calculation for UART baud rate */
#define FOSC 8000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void)
{
	/* Local Variables */
	unsigned char cmd = 0;
	
	/* Initialize software modules */
	UART_init(MYUBRR);	/* Initialize UART */
	SPI_MasterInit();	/* Initialize SPI */
	
	sei();	/* Enable global interrupts */
	
	char hi[] = "Hello World!\n\r";
	char *txt = hi;
	
	while(1)
	{
		UART_putc('x');
		_delay_ms(1000);
	}	/* End of while */
	return 0;
}	/* End of main */