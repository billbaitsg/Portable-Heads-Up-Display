/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	GPS
	
	Module:	UART functions
	
	Desc.:	This file contains the source code for the
			functions for the UART module.  Much of the 
			code for this module is taken from the 
			ATTiny2313 datasheet.
**********************************************************/

#include "proj_hdr.h"

/* Global Variables */
//volatile char UART_BUFFER[UART_BUFFER_SIZE];		/* Set size of UART buffer */
//volatile char UART_BUF_CNT = 0;				/* UART Buffer position counter */
//volatile char UART_FLAGS = 0;	/* "Register" to store UART status */

/* Initialize UART module, from datasheet */
void UART_init( void )
{
	/* UBRR = (fosc/16/baud)-1 = (8MHz/16/9600bps)-1 = 51.083 = 51 */
	unsigned int ubrr = 51;
	/* Set baud rate */
	UBRRH = (unsigned char)(ubrr>>8);
	UBRRL = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8 data, 1 stop bit */
	UCSRC = (0<<USBS)|(3<<UCSZ0);
	/* Enable the USART Recieve Complete interrupt (USART_RXC) */
	UCSRB |= (1<<RXCIE);	
}

/* Send a byte via UART, from datasheet */
void UART_putc( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}

/* Get a byte via UART, from datasheet */
unsigned char UART_getc( void )
{
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;
}

/* Flush out the UART receive buffer, from datasheet */
void UART_flush( void )
{
	unsigned char dummy;
	while ( UCSRA & (1<<RXC) ) dummy = UDR;
}

/* UART receive complete interrupt */
volatile unsigned char COUNT = 0;
volatile unsigned int TEMP = 0;
ISR( USART_RX_vect )
{
	/* Local Variables */
	unsigned char rx = 0;
	
	/* Wait for completion of transmit (should be redundant) */
	while ( !(UCSRA & (1<<RXC)) ){}
	
	rx = UDR;	/* Read UART Data Register into local variable */
	
	if( rx == '$' )	/* if start new sentence */
	{
		COUNT = 0;	/* reset count */
		NMEA_TYPE = 0;	/* reset NMEA type */
	}

	if( COUNT == 1 )	/* first character should always be G */
	{
		if( rx != 'G' )	/* if it's not a G */
		{
			COUNT = 83;	/* set count to higher than max */
		}
	}

	if( COUNT == 2 )	/* second character should always be P */
	{
		if( rx != 'P' )	/* if it's not a G */
		{
			COUNT = 83;	/* set count to higher than max */
		}
	}

	if( COUNT == 3 )	/* third char should be V or G */
	{
		if( rx == 'V' )	/* if it's a V */
		{
			NMEA_TYPE = 6;	/* set VTG type */
		}
		else if( rx == 'G' )	/* if it's a G */
		{
			NMEA_TYPE = 1;	/* set GGA type */
		}
		else
		{
			NMEA_TYPE = 0;	/* set no type */
			COUNT = 83;	/* set count higher than max */
		}
	}

	if( COUNT == 4 ) 	/* continue checking for VTG or GGA type */
	{
		if( rx == 'T' && NMEA_TYPE == 6 )	/* if VTG is still valid */
		{
			NMEA_TYPE = 6;	/* keep VTG type */
		}
		else if( rx == 'G' && NMEA_TYPE == 1 )	/* if GGA is still valid */
		{
			NMEA_TYPE = 1;	/* keep GGA type */
		}
		else
		{
			NMEA_TYPE = 0;	/* no type */
			COUNT = 83;	/* > max */
		}
	}

	if( COUNT == 5 ) 	/* continue checking for VTG or GGA type */
	{
		if( rx == 'G' && NMEA_TYPE == 6 )	/* if VTG is still valid */
		{
			NMEA_TYPE = 6;	/* keep VTG type */
		}
		else if( rx == 'A' && NMEA_TYPE == 1 )	/* if GGA is still valid */
		{
			NMEA_TYPE = 1;	/* keep GGA type */
		}
		else
		{
			NMEA_TYPE = 0;	/* no type */
			COUNT = 83;	/* > max */
		}
	}

	if( COUNT == 7 )
	{
		if( NMEA_TYPE == 1 )	/* GPGGA */
		{
			TEMP = 0;
			TEMP += (rx-48)*10;	/* tens digit of hours */
		}
		else if( NMEA_TYPE == 6 )	/* GPVTG */
		{
			TEMP = 0;
			TEMP += (rx-48)*1000;	/* thousands digit of course */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 8 )
	{
		if( NMEA_TYPE == 1 )	/* GPGGA */
		{
			TEMP += (rx-48);	/* ones digit of hours */
			HOURS = TEMP;		/* set HOURS to temp */
		}
		else if( NMEA_TYPE == 6 )	/* GPVTG */
		{
			TEMP += (rx-48)*100;	/* hundreds digit of course */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 9 )
	{
		if( NMEA_TYPE == 1 )	/* GPGGA */
		{
			TEMP = 0;
			TEMP += (rx-48)*10;	/* tens digit of minutes */
		}
		else if( NMEA_TYPE == 6 )	/* GPVTG */
		{
			TEMP += (rx-48)*10;	/* tens digit of course */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 10 )
	{
		if( NMEA_TYPE == 1 )	/* GPGGA */
		{
			TEMP += (rx-48);	/* ones digit of minutes */
			MINUTES = TEMP;	/* set MINUTES to temp */
		}
		else if( NMEA_TYPE == 6 )	/* GPVTG */
		{
			if( rx == '.' )	/* should be a decimal point */
			{
				NMEA_TYPE = 6;	/* keep GPVTG */
			}
			else	/* oopsie */
			{
				NMEA_TYPE = 0;
				COUNT = 83;
			}
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 11 )
	{
		if( NMEA_TYPE == 1 )	/* GPGGA */
		{
			TEMP = 0;
			TEMP += (rx-48)*10;	/* tens digit of seconds */
		}
		else if( NMEA_TYPE == 6 )	/* GPVTG */
		{
			TEMP += (rx-48);	/* ones digit of course */
			BEARING = TEMP;	/* set BEARING to temp */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 12 )
	{
		if( NMEA_TYPE == 1 )	/* GPGGA */
		{
			TEMP += (rx-48);	/* ones digit of seconds */
			SECONDS = TEMP;		/* set SECONDS to temp */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	/* Parse out speed */
	if( COUNT == 25 )
	{
		if( NMEA_TYPE == 6 )	/* GPVTG */
		{
			TEMP = 0;	/* reset temp */
			TEMP += (rx-48)*10000;	/* ten thousands digit of speed */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 26 )
	{
		if( NMEA_TYPE == 6 )	/* GPVTG */
		{
			TEMP += (rx-48)*1000;	/* thousands digit of speed */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 27 )
	{
		if( NMEA_TYPE == 6 )	/* GPVTG */
		{
			TEMP += (rx-48)*100;	/* hundreds digit of speed */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 28 )
	{
		if( NMEA_TYPE == 6 )	/* GPVTG */
		{
			TEMP += (rx-48)*10;	/* tens digit of speed */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 29 )
	{
		if( NMEA_TYPE == 6 )	/* GPVTG */
		{
			if( rx == '.' )	/* should be a decimal point */
			{
				NMEA_TYPE = 6;	/* keep GPVTG */
			}
			else	/* oopsie */
			{
				NMEA_TYPE = 0;
				COUNT = 83;
			}
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 30 )
	{
		if( NMEA_TYPE == 6 )	/* GPVTG */
		{
			TEMP += (rx-48);	/* ones digit of speed */
			SPEED = TEMP;	/* set SPEED to temp */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}
	/* end of speed parser */

	/* start altitude parser */
	if( COUNT == 51 )
	{
		if( NMEA_TYPE == 1 )	/* GPGGA */
		{
			TEMP = 0;
			if( rx == '-' )		/* if altitude is negative */
			{
				/* do nothing for now */
			}
			else
			{
				TEMP += (rx-48)*100000;	/* hundred thousands digit of altitude */
			}
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 52 )
	{
		if( NMEA_TYPE == 1 )	/* GPGGA */
		{
			TEMP += (rx-48)*10000;	/* ten thousands digit of altitude */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 53 )
	{
		if( NMEA_TYPE == 1 )	/* GPGGA */
		{
			TEMP += (rx-48)*100;	/* thousands digit of altitude */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 54 )
	{
		if( NMEA_TYPE == 1 )	/* GPGGA */
		{
			TEMP += (rx-48)*100;	/* hundreds digit of altitude */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 55 )
	{
		if( NMEA_TYPE == 1 )	/* GPGGA */
		{
			TEMP += (rx-48)*10;	/* tens digit of altitude */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 56 )
	{
		if( NMEA_TYPE == 1 )	/* GPGGA */
		{
			if( rx == '.' )	/* should be a decimal point */
			{
				NMEA_TYPE = 6;	/* keep GPVTG */
			}
			else	/* oopsie */
			{
				NMEA_TYPE = 0;
				COUNT = 83;
			}
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}

	if( COUNT == 57 )
	{
		if( NMEA_TYPE == 1 )	/* GPGGA */
		{
			TEMP += (rx-48);	/* ones digit of altitude */
			ALTITUDE = TEMP;	/* set ALTITUDE to temp */
		}
		else	/* oopsie state */
		{
			NMEA_TYPE = 0;	/* reset type */
			COUNT = 83;		/* reset count */
		}
	}
	/* end of altitude parser */


	COUNT++;	/* increment count */

	//UART_putc(rx);	/* echo received character */

	/* if BUFFER_SIZE is reached, reset to start of buffer */
//	if (UART_BUF_CNT==UART_BUFFER_SIZE)
//	{
//		UART_BUF_CNT = 0;
//	}/* End of if */
//
//	/* Check for start or end of GPS NMEA sentence */
//	if( rx == 0x24 )		/* $ - indicates start of NMEA sentence */
//	{
//		UART_BUF_CNT = 0;	/* Reset UART Buffer Counter */
//		UART_BUFFER[UART_BUF_CNT++] = rx;	/* Store into UART Buffer */
//		NMEA_FLAGS |= (1<<NMEA_START);	/* Set NMEA sentence started flag */
//	}
//	else if( rx == '\n' )	/* Carraige Return, New Line - indicates end of sentence 8 */
//	{
//		UART_BUFFER[UART_BUF_CNT++] = rx;	/* Store into UART Buffer */
//		if( UART_BUFFER[UART_BUF_CNT-2] == '\r' )	/* If the previous character was CR */
//		{
//			NMEA_FLAGS |= (1<<NMEA_RXC);	/* Set NMEA Sentence receive complete flag */
//			/* If the NMEA Sentence is both started and finished */
//			if( NMEA_FLAGS == (1<<NMEA_START)|(1<<NMEA_RXC) )
//			{
//				for(rx = 0; rx < UART_BUF_CNT; rx++)
//				{
//					NMEA_SENTENCE[rx] = UART_BUFFER[rx];	/* Copy UART buffer into NMEA Sentence */
//				}/* end for loop */
//				NMEA_SENT_ptr = NMEA_SENTENCE;	/* Point NMEA_SENT_ptr to NMEA_SENTENCE */
//				/* If a GPVTG sentence is detected */
//				if( NMEA_SENTENCE[3] == 'V' && NMEA_SENTENCE[4] == 'T' && NMEA_SENTENCE[5] == 'G' )
//				{
//					GPVTG_parser(NMEA_SENT_ptr);
//				}
//				/* Else if a GPGGA sentence is detected */
//				else if( NMEA_SENTENCE[3] == 'G' && NMEA_SENTENCE[4] == 'G' && NMEA_SENTENCE[5] == 'A' )
//				{
//					GPGGA_parser(NMEA_SENT_ptr);
//				}
//				else	/* Else, oopsies */
//				{
//					NMEA_FLAGS = 0;
//					NMEA_FLAGS = (1<<NMEA_ERROR);	/* Set NMEA error flag */
//				}/* end if */
//			}
//		}
//	}
//	else
//	{
//		/* Put character in buffer and increment counter */
//		UART_BUFFER[UART_BUF_CNT++] = rx;
//	}
}
