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
volatile char UART_BUFFER[UART_BUFFER_SIZE];		/* Set size of UART buffer */
volatile char UART_BUF_CNT = 0;				/* UART Buffer position counter */
volatile char UART_FLAGS = 0;	/* "Register" to store UART status */

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
ISR( USART_RX_vect )
{
	/* Wait for completion of transmit (should be redundant) */
	while ( !(UCSRA & (1<<RXC)) );	
	/* if BUFFER_SIZE is reached, reset to start of buffer */
	if (UART_BUF_CNT==UART_BUFFER_SIZE) 
	{
		UART_BUF_CNT=0;
	}/* End of if */
	/* Put character in buffer and increment counter */
	UART_BUFFER[UART_BUF_CNT++] = UDR;
	/* Put up UART recieve byte complete flag */
	UART_FLAGS |= (1<<UART_RXC);	
}

/* UART transmit complete interrupt */
ISR( USART_TX_vect )
{
	
}

/* UART data register empty */
ISR( USART_UDRE_vect )
{

}