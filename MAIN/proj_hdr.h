/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Main Controller

	Module:	Project header
	
	Desc.:	This file contains information useful to all
			modules in this block, namely global variables
			and include files
**********************************************************/

#ifndef PROJ_HDR_H
#define PROJ_HDR_H

	/* Include Files */
	#include <avr/io.h>
	#include <avr/interrupt.h>
	#include <util/delay.h>
	#include <stdio.h>
	/* Module Includes */
	#include "spi.h"
	#include "uart.h"
	
	/* SPI Slave Select Macros */
	#define GPS_SS_0 (PORTD &= ~0x04)	/* Set GPS SS low */
	#define GPS_SS_1 (PORTD |= 0x04)	/* Set GPS SS high */
	#define ACC_SS_0 (PORTD &= ~0x08)	/* Set Accelerometer SS low */
	#define ACC_SS_1 (PORTD |= 0x08)	/* Set Accelerometer SS high */
	#define AMB_SS_0 (PORTD &= ~0x20)	/* Set Ambient SS low */
	#define AMB_SS_1 (PORTD |= 0x20)	/* Set Ambient SS high */
	#define RNG_SS_0 (PORTD &= ~0x40)	/* Set Range SS low */
	#define RNG_SS_1 (PORTD |= 0x40)	/* Set Range SS high */
	#define DIS_SS_0 (PORTD &= ~0x80)	/* Set Display SS low */
	#define DIS_SS_1 (PORTD |= 0x80)	/* Set Display SS high */

	/* Global Variables */

#endif