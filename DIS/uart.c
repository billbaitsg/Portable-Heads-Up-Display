/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Display Controller
	
	Module:	UART functions
	
	Desc.:	This file contains the source code for the
			functions for the UART module.  Much of the 
			code for this module is taken from the 
			ATTiny2313 datasheet.
**********************************************************/

#include "proj_hdr.h"

/* Global Variables */
volatile unsigned char UART_BUFFER[UART_BUFFER_SIZE];		/* Set size of UART buffer */
volatile unsigned char UART_BUF_CNT = 0;				/* UART Buffer position counter */
volatile unsigned char UART_FLAGS = 0;	/* "Register" to store UART status */

/* Initialize UART module, from datasheet */
void UART_init( unsigned int ubrr )
{
	/* Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 7 data, 1 stop, odd parity */
	UCSR0C = (1<<UCSZ01)|(1<<UPM01)|(1<<UPM00);	/* 7 data bits, odd parity */
	/* Enable the USART Receive Complete interrupt (USART_RXC) */
	//UCSR0B |= (1<<RXCIE0);	
}

/* Send a byte via UART, from datasheet */
void UART_putc( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

/* Send a string via UART */
void UART_puts(unsigned char * string )
{
	unsigned char n = 0;
	while( n < strlen(string) )	/* while not at the end of the string */
	{
		UART_putc(string[n++]);	/* putc the next character */
	}/* end while */
}

/* Get a byte via UART, from datasheet */
unsigned char UART_getc( void )
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

/* Flush out the UART receive buffer, from datasheet */
void UART_flush( void )
{
	unsigned char dummy;
	while ( UCSR0A & (1<<RXC0) ) dummy = UDR0;
}
