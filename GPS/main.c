/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	GPS
	
	Module:	Main program
	
	Desc.:	This is the main program section of the 
			Ambient Light microcontroller
**********************************************************/

#include "proj_hdr.h"	/* Include project header file */

int main(void)
{
	/* Local Variables */
	unsigned char cmd = 0;
	
	/* Initialize software modules */
	USI_SPI_initslave();	/* Initialize SPI as slave */
	UART_init();			/* Initialize UART for 9600, 8N1 */
	
	sei();	/* Enable global interrupts */
	
	while(1)
	{
		// cmd = USI_SPI_getc();
		// if( cmd == 'H' ) 		/* Heading requested */
		// {
		
		// }
		// else if( cmd == "V" )	/* Speed requested (Velocity) */
		// {
		
		// }
		// else if( cmd == "A" )	/* Altitude requested */
		// {
		
		// }
		// else if( cmd == "T" )	/* Time requested */
		// {
		
		// }
		// else					/* Ignore all other requests */
		// {}	/* End of if */
	}	/* End of while */
	return 0;
}	/* End of main */