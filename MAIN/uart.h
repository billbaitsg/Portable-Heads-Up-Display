/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Main Controller
	
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
	ISR( USART_RXC_vect );
	ISR( USART_TXC_vect );
	ISR( USART_DRE_vect );
	
	/* Global Variables */
	extern volatile char UART_BUFFER[];
	
	/* Defines */
	#define UART_BUFFER_SIZE 8	/* Set max buffer size */
	//#define UART_RXC	0	/* UART finished receiving byte flag */
	//#define UART_TXC	1	/* UART finished transmitting byte flag */
#endif