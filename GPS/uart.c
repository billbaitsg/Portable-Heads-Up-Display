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

/* Initialize UART module, from datasheet */
void UART_init( unsigned int baud )
{
	/* Set baud rate */
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Set frame format: 8 data, 1 stop bit */
	UCSRC = (0<<USBS)|(3<<UCSZ0);
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
ISR( USART0_RXC_vect )
{

}

/* UART transmit complete interrupt */
ISR( USART0_TXC_vect )
{

}

/* UART data register empty */
ISR( USART0_DRE_vect )
{

}