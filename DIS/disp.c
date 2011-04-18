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
	
	/* Set cursor position */
	UART_puts("\n\r\t  X= ");		/* Print information */

	if( X_AXIS == 0 )	/* if X-axis value is still at default */
	{
		UART_puts("NO VAL");	/* Print error message */
		return;	/* exit function */
	}
	else if( X_AXIS > 214 )	/* if X-axis value is >max value */
	{
		UART_putc('>');	/* Print the greater than sign */
		sign = '-';		/* Set sign to negative */
		accel = 360;	/* Set acceleration value to absolute maximum */
	}
	else if( X_AXIS < 40 ) /* if X-axis value is <min value */
	{
		UART_putc('<');	/* Print the less than sign */
		sign = '+';		/* Set sign to positive */
		accel = 360;	/* Set acceleration value to absolute maximum */
	}
	else if( X_AXIS >= 128 )	/* if X-axis has negative g */
	{
		sign = '-';		/* Set sign to negative */
		accel = (((float)(X_AXIS-128)/24)*100);	/* Calculate Acceleration */
	}
	else				/* else X-axis has positive g */
	{
		sign = '+';		/* Set sign to positive */
		accel = (((float)(128-X_AXIS)/24)*100);	/* Calculate Acceleration */
	}/* end if */
	
	/* Print X-axis sign and value */
	UART_putc(sign);					/* Print the + or - sign */
	UART_putc( (accel/100)+0x30 );		/* Print the 100's digit */
	UART_putc('.');						/* Print the decimal point */
	UART_putc( ((accel/10)%10)+0x30 );	/* Print the 10's digit */
	UART_putc( (accel%10)+0x30 );		/* Print the 1's digit */
	UART_puts("G ");					/* Append the units */
}

/* Print the Y-axis Accelerometer value to the VFD */
void display_y(void)
{
	/* Local Variables */
	unsigned char sign = 0;	/* + or - */
	unsigned int accel = 0;	/* 000 to 360 for 0.00G to 3.60G*/
	
	/* Set cursor position */
	UART_puts("\n\r\t  Y= ");		/* Print information */

	if( Y_AXIS == 0 )	/* if Y-axis value is still at default */
	{
		UART_puts("NO VAL");	/* Print error message */
		return;	/* exit function */
	}
	else if( Y_AXIS > 214 )	/* if Y-axis value is >max value */
	{
		UART_putc('>');	/* Print the greater than sign */
		sign = '-';		/* Set sign to negative */
		accel = 360;	/* Set acceleration value to absolute maximum */
	}
	else if( Y_AXIS < 40 ) /* if Y-axis value is <min value */
	{
		UART_putc('<');	/* Print the less than sign */
		sign = '+';		/* Set sign to positive */
		accel = 360;	/* Set acceleration value to absolute maximum */
	}
	else if( Y_AXIS >= 128 )	/* if Y-axis has negative g */
	{
		sign = '-';		/* Set sign to negative */
		accel = (((float)(Y_AXIS-128)/24)*100);	/* Calculate Acceleration */
	}
	else				/* else Y-axis has positive g */
	{
		sign = '+';		/* Set sign to positive */
		accel = (((float)(128-Y_AXIS)/24)*100);	/* Calculate Acceleration */
	}/* end if */
	
	/* Print Y-axis sign and value */
	UART_putc(sign);					/* Print the + or - sign */
	UART_putc( (accel/100)+0x30 );		/* Print the 100's digit */
	UART_putc('.');						/* Print the decimal point */
	UART_putc( ((accel/10)%10)+0x30 );	/* Print the 10's digit */
	UART_putc( (accel%10)+0x30 );		/* Print the 1's digit */
	UART_puts("G ");					/* Append the units */
}

/* Print the Z-axis Accelerometer value to the VFD */
void display_z(void)
{
	/* Local Variables */
	unsigned char sign = 0;	/* + or - */
	unsigned int accel = 0;	/* 000 to 360 for 0.00G to 3.60G*/
	
	/* Set cursor position */
	UART_puts("\n\r\t  Z= ");		/* Print information */

	if( Z_AXIS == 0 )	/* if Z-axis value is still at default */
	{
		UART_puts("NO VAL");	/* Print error message */
		return;	/* exit function */
	}
	else if( Z_AXIS > 214 )	/* if Z-axis value is >max value */
	{
		UART_putc('>');	/* Print the greater than sign */
		sign = '-';		/* Set sign to negative */
		accel = 360;	/* Set acceleration value to absolute maximum */
	}
	else if( Z_AXIS < 40 ) /* if Z-axis value is <min value */
	{
		UART_putc('<');	/* Print the less than sign */
		sign = '+';		/* Set sign to positive */
		accel = 360;	/* Set acceleration value to absolute maximum */
	}
	else if( Z_AXIS >= 128 )	/* if Z-axis has negative g */
	{
		sign = '-';		/* Set sign to negative */
		accel = (((float)(Z_AXIS-128)/24)*100);	/* Calculate Acceleration */
	}
	else				/* else Z-axis has positive g */
	{
		sign = '+';		/* Set sign to positive */
		accel = (((float)(128-Z_AXIS)/24)*100);	/* Calculate Acceleration */
	}/* end if */
	
	/* Print Z-axis sign and value */
	UART_putc(sign);					/* Print the + or - sign */
	UART_putc( (accel/100)+0x30 );		/* Print the 100's digit */
	UART_putc('.');						/* Print the decimal point */
	UART_putc( ((accel/10)%10)+0x30 );	/* Print the 10's digit */
	UART_putc( (accel%10)+0x30 );		/* Print the 1's digit */
	UART_puts("G ");					/* Append the units */
}

/* Print the Range Finder value */
void display_r(void)
{
	/* Local Variables */
	unsigned char dist = 0;

	/* Set cursor position */
	UART_puts("\n\r\t  R= ");		/* Print information */

	if( RANGE == 0 )	/* if Range vale is still at default */
	{
		UART_puts("NO VAL");	/* Print error message */
		return;	/* quit function */
	}

	/* Display Range value */
	dist = 180 - RANGE;//(float)(RANGE*65)-12.5;
	UART_putc( (dist/100)+0x30 );		/* Print the 100's digit */
	UART_putc( ((dist/10)%10)+0x30 );	/* Print the 10's digit */
	UART_putc( (dist%10)+0x30 );		/* Print the 1's digit */
	UART_puts("cm ");
}

/* Print the Ambient Light value */
void display_l(void)
{
	/* Set cursor position */
	UART_puts("\n\r\t  L= ");		/* Print information */

	if( LIGHT == 0 )	/* if Light value is still at default */
	{
		UART_puts("NO VAL");	/* Print error message */
		return;	/* quit function */
	}
	else if( LIGHT > 200 )	/* if it's dark */
	{
		brightness(1);	/* dimmest display level */
	}
	else if( LIGHT > 150 )
	{
		brightness(2);
	}
	else if( LIGHT > 100 )
	{
		brightness(3);
	}
	else
	{
		brightness(4);	/* brightest display level */
	}

	/* Display Ambient Light value */
	UART_putc( (LIGHT/100)+0x30 );		/* Print the 100's digit */
	UART_putc( ((LIGHT/10)%10)+0x30 );	/* Print the 10's digit */
	UART_putc( (LIGHT%10)+0x30 );		/* Print the 1's digit */
	UART_puts("   ");
}

/* Print the Altitude value */
void display_a(void)
{
	/* Set cursor position */
	UART_puts("\n\r\t\t\t  A= ");	/* Print information */

	if( ALTITUDE < 0 )	/* if Altitude is negative */
	{
		UART_putc('-');	/* Print a negative sign */
	}

	/* Display Altitude value */
	UART_putc( (ALTITUDE/10000)%10+0x30 );		/* Print the 10000's digit */
	UART_putc( (ALTITUDE/1000)%10+0x30 );		/* Print the 1000's digit */
	UART_putc( (ALTITUDE/100)%10+0x30 );		/* Print the 100's digit */
	UART_putc( (ALTITUDE/10)%10+0x30 );			/* Print the 10's digit */
	UART_putc( (ALTITUDE%10)+0x30 );			/* Print the 1's digit */
	UART_puts("m  ");
}

/* Print the Speed value */
void display_v(void)
{
	/* Set cursor position */
	UART_puts("\n\r\t\t\t  S= ");	/* Print information */

	/* Display Speed value */
	UART_putc( (SPEED/10000)%10+0x30 );		/* Print the 1000's digit */
	UART_putc( (SPEED/1000)%10+0x30 );		/* Print the 100's digit */
	UART_putc( (SPEED/100)%10+0x30 );			/* Print the 10's digit */
	UART_putc( (SPEED/10)%10+0x30 );			/* Print the 1's digit */
	UART_putc( '.' );	/* Print decimal point */
	UART_putc( SPEED%10+0x30 );			/* Print the tenthes digit */
	UART_puts("kmh ");
}

/* Print the Bearing */
void display_b(void)
{
	/* Set cursor position */
	UART_puts("\n\r\t\t\t  B= ");	/* Print information */

	/* Display Bearing value */
	UART_putc( (BEARING/1000)%10+0x30 );		/* Print the 100's digit */
	UART_putc( (BEARING/100)%10+0x30 );		/* Print the 10's digit */
	UART_putc( (BEARING/10)%10+0x30 );			/* Print the 1's digit */
	UART_putc( '.' );	/* Print decimal point */
	UART_putc( (BEARING)%10+0x30 );			/* Print the tenthes digit */
	UART_puts("deg");
}

/* Print the Time */
void display_time(void)
{
	/* Set cursor position */
	UART_puts("\n\r\t\t\t  ");	/* Print information */
	/* Display Time */
	UART_putc( ((HOURS/10)%10)+0x30 );	/* Print the 10's digit */
	UART_putc( (HOURS%10)+0x30 );		/* Print the 1's digit */
	UART_putc(':');
	UART_putc( ((MINUTES/10)%10)+0x30 );	/* Print the 10's digit */
	UART_putc( (MINUTES%10)+0x30 );		/* Print the 1's digit */
	UART_putc(':');
	UART_putc( ((SECONDS/10)%10)+0x30 );	/* Print the 10's digit */
	UART_putc( (SECONDS%10)+0x30 );		/* Print the 1's digit */
}

volatile unsigned char COUNT = 0;
/* Print a simple counter */
void display_counter(void)
{

	UART_putc( (COUNT/100)%10+0x30 );		/* Print the 100's digit */
	UART_putc( (COUNT/10)%10+0x30 );		/* Print the 10's digit */
	UART_putc( (COUNT%10)+0x30 );			/* Print the 1's digit */
	COUNT++;
}
