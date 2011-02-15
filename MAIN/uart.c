/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Main Controller
	
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
	/* Set frame format: 8 data, 1 stop bit */
	UCSR0C = (0<<USBS0)|(3<<UCSZ00);
	/* Enable the USART Recieve Complete interrupt (USART_RXC) */
	UCSR0B |= (1<<RXCIE0);	
}

/* Send a byte via UART, from datasheet */
void UART_putc( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
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

/* UART receive complete interrupt */
ISR( USART_RXC_vect )
{
	/* Wait for completion of transmit (should be redundant) */
	while ( !(UCSR0A & (1<<RXC0)) );	
	/* if BUFFER_SIZE is reached, reset to start of buffer */
	if (UART_BUF_CNT==UART_BUFFER_SIZE) 
	{
		UART_BUF_CNT=0;
	}/* End of if */
	/* Put character in buffer and increment counter */
	UART_BUFFER[UART_BUF_CNT++] = UDR0;
	/* Put up UART recieve byte complete flag */
	//UART_FLAGS |= (1<<UART_RXC);	
}

/* UART transmit complete interrupt */
ISR( USART_TXC_vect )
{
	
}

/* UART data register empty */
ISR( USART_DRE_vect )
{

}