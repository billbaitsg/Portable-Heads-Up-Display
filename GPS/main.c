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
		if( !USI_SS )	/* if this SPI slave is selected */
		{
			USI_SPI_SSn(0);		/* Active low slave selected */
			cmd = USI_SPI_getc();
			if( cmd == 'B' ) 		/* Heading requested */
			{
				USI_SPI_putc( (unsigned char)(BEARING>>8) );	/* send high byte of Bearing */
				USI_SPI_wait();
				USI_SPI_putc( (unsigned char)BEARING );	/* send low byte of Bearing */
				USI_SPI_wait();
			}
			else if( cmd == 'V' )	/* Speed requested (Velocity) */
			{
				USI_SPI_putc( (unsigned char)(SPEED>>8) );	/* send high byte of Speed */
				USI_SPI_wait();
				USI_SPI_putc( (unsigned char)SPEED );	/* send low byte of Speed */
				USI_SPI_wait();
			}
			else if( cmd == 'A' )	/* Altitude requested */
			{
				USI_SPI_putc( (unsigned char)(ALTITUDE>>8) );	/* send high byte of Altitude */
				USI_SPI_wait();
				USI_SPI_putc( (unsigned char)ALTITUDE );	/* send low byte of Altitude */
				USI_SPI_wait();
			}
			else if( cmd == 'H' )	/* Hours requested */
			{
				USI_SPI_putc( HOURS );	/* send Hours */
				USI_SPI_wait();
			}
			else if( cmd == 'M' )	/* Minutes requested */
			{
				USI_SPI_putc( MINUTES );	/* send Minutes */
				USI_SPI_wait();
			}
			else if( cmd == 'S' )	/* Seconds requested */
			{
				USI_SPI_putc( SECONDS );	/* send Seconds */
				USI_SPI_wait();
			}
			else					/* Ignore all other requests */
			{}	/* End of if */
		}
		else	/* if not selected, do nothing */
		{
			USI_SPI_SSn(1);		/* Active low slave not selected */
		}/* End of if */
		
	}	/* End of while */
	return 0;
}	/* End of main */
