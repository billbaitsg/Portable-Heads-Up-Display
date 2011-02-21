/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Display Controller
	
	Module:	Display Output functions
	
	Desc.:	This file contains the source code for the
			functions for the Display Outputs module.
**********************************************************/

#include "proj_hdr.h"
/* 24 per G (ADXL335 is ratiometric) */
/* 0.00G is 127 */
/* Max is 127-(3.6*24), Min is 127+(3.6*24) */
/* Max value is 214 (-3.6G) */
/* Min value is 40 (+3.6G) */

/* Print the X-axis Accelerometer value to the VFD */
void display_x(void)
{
	/* Local Variables */
	unsigned char sign = 0;	/* + or - */
	unsigned int accel = 0;	/* 000 to 360 for 0.00G to 3.60G*/
	
	
	if( X_AXIS > 214 )	/* 
	else if( X_AXIS >= 128 )	/* if X-axis has negative g */
	{
		sign = '-';		/* Set sign to negative */
		accel = (float)(((X_AXIS-128)/24)*100);	/* Calculate Acceleration */
	}
	else				/* else X-axis has positive g */
	{
		sign = '+';		/* Set sign to positive */
		accel = (float)(((128-X_AXIS)/24)*100);	/* Calculate Acceleration */
	}
	
	cursor_position(8,0);	/* 2nd row, 1st column */
	UART_putc(sign);		/* Print the + or - sign */
	UART_putc(accel/100);	/* Print the 100's digit */
	UART_putc('.');			/* Print the decimal point */
	UART_putc((accel/10)%10);	/* Print the 10's digit */
	UART_putc(accel%10);	/* Print the 1's digit */
}