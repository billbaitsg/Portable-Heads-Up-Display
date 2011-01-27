/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Range Finder 

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
/* Module Includes */
#include "adc.h"
#include "usi.h"
	
/* ADC Global Variables */
extern volatile char RANGE;

#endif