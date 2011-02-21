/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Display Controller

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
	#include "vfd.h"
	#include "disp.h"
	
	/* Global Variables */
	extern volatile unsigned char X_AXIS;	/* X-axis acceleration */
	extern volatile unsigned char Y_AXIS;	/* Y-axis acceleration */
	extern volatile unsigned char Z_AXIS;	/* Z-axis acceleration */
	extern volatile unsigned char RANGE;	/* Range finder distance */
	extern volatile unsigned char LIGHT;	/* Ambient light level */
	extern volatile int ALTITUDE;			/* Altitude in meters */
	extern volatile unsigned int SPEED;	/* Speed in kilometers per hour */
	extern volatile unsigned char BEARING;	/* Heading of the vehicle */
	extern volatile unsigned char HOURS;	/* Hour of the current time */
	extern volatile unsigned char MINUTES;	/* Minutes of the current hour */
	extern volatile unsigned char SECONDS;	/* Seconds of the current hour */
	
#endif