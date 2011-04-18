/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Display Controller
	
	Module:	UART header
	
	Desc.:	This file contains the global variables and 
			function prototypes for the UART module.
**********************************************************/

#ifndef UART_H
#define UART_H

	/* Function prototypes */
	void UART_init( unsigned int baud );
	void UART_putc( unsigned char data );
	void UART_puts( unsigned char * string );
	unsigned char UART_getc( void );
	void UART_flush( void );
	
	/* Global Variables */
	extern volatile unsigned char UART_BUFFER[];
	
	/* Defines */
	#define UART_BUFFER_SIZE 8	/* Set max buffer size */
	//#define UART_RXC	0	/* UART finished receiving byte flag */
	//#define UART_TXC	1	/* UART finished transmitting byte flag */
#endif