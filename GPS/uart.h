/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	GPS
	
	Module:	UART header
	
	Desc.:	This file contains the global variables and 
			function prototypes for the UART module.
**********************************************************/

#ifndef UART_H
#define UART_H

	/* Function prototypes */
	void UART_init( unsigned int baud );
	void UART_putc( unsigned char data );
	unsigned char UART_getc( void );
	void UART_flush( void );
	ISR( USART0_RXC_vect );
	ISR( USART0_TXC_vect );
	ISR( USART0_DRE_vect );
	
#endif