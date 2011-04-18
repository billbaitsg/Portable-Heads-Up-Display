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

	/* Includes */
	//#include <string.h>

	/* Function prototypes */
	void UART_init( void );
	void UART_putc( unsigned char data );
	unsigned char UART_getc( void );
	void UART_flush( void );
	ISR( USART_RX_vect );
	
	/* Global Variables */
	extern volatile char UART_BUFFER[];
	
	/* Defines */
	#define UART_BUFFER_SIZE 82	/* Set max buffer size as max NMEA sentence size */
	#define UART_RXC	0	/* UART finished receiving byte flag */
	#define UART_TXC	1	/* UART finished transmitting byte flag */
#endif
