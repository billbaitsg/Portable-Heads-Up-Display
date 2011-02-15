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

int main(void)
{
	/* Local Variables */
	unsigned char cmd = 0;
	
	/* Initialize software modules */
	UART_init(9800);
	
	sei();	/* Enable global interrupts */
	
	char hi[] = "Hello World!\n\r";
	char *txt = hi;
	
	while(1)
	{
		printf(txt);
		UART_putc('x');
		_delay_ms(1000);
	}	/* End of while */
	return 0;
}	/* End of main */