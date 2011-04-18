/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Display Controller
	
	Module:	VFD Command functions
	
	Desc.:	This file contains the source code for the
			functions for the VFD commands module.
			
	WARNING: Functions are not protected for invalid inputs
**********************************************************/

#include "proj_hdr.h"

/* Global Variables */
volatile unsigned char row_report = 0;
volatile unsigned char col_report = 0;
volatile unsigned char cursor_responded = 0;

/* Moves cursor to home position */
void cursor_home(void)	/* works */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x5B);	/* [ */
	UART_putc(0x48);	/* H */
}

/* Moves the cursor up 1-6 lines in the same column, stops at the top */
void cursor_up(unsigned char lines)	/* unknown */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x5B);	/* [ */
	UART_putc(0x30+lines);	/* number of lines */
	UART_putc(0x41);	/* A */
}

/* Moves the cursor down 1-6 lines in the same column, stops at the bottom */
void cursor_down(unsigned char lines)	/* unknown */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x5B);	/* [ */
	UART_putc(0x30+lines);	/* number of lines */
	UART_putc(0x42);	/* B */
}

/* Moves the cursor right 1-9 columns, stops at the right margin */
void cursor_right(unsigned char cols)	/* unknown */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x5B);	/* [ */
	UART_putc(0x30+cols);	/* number of lines */
	UART_putc(0x43);	/* C */	
}

/* Moves the cursor left 1-9 columns, stops at the left margin */
void cursor_left(unsigned char cols)	/* unknown */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x5B);	/* [ */
	UART_putc(0x30+cols);	/* number of lines */
	UART_putc(0x44);	/* D */	
}

/* Moves the cursor to an arbitrary position */
void cursor_position(unsigned char row, unsigned char col)	/* DOES NOT work */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x5B);	/* [ */
	UART_putc(0x30+(row/10));	/* Row, 10's digit */
	UART_putc(0x30+(row%10));	/* Row, 1's digit */
	UART_putc(0x3B);	/* ; */
	UART_putc(0x30+(col/100));	/* Column, 100's digit */
	UART_putc(0x30+((col/10)%10));	/* Column, 10's digit */
	UART_putc(0x30+(col%10));	/* Column, 1's digit */
	UART_putc(0x52);	/* R */
}

/* Saves the present value of the cursor location, 
character attribute, and character set selection,
moves to home if none were saved */
void save_cursor(void)	/* unknown */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x37);	/* 7 */
}

/* Restores the previously saved cursor position */
void restore_cursor(void)	/* unknown */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x38);	/* 8 */
}

/* Request cursor position */
void request_cursor(void)	/* unknown, probably doesnt work */
{
	row_report = 0;
	col_report = 0;
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x5B);	/* [ */
	UART_putc(0x36);	/* 6 */
	UART_putc(0x6E);	/* n */	
	UART_getc();		/* ESC */
	UART_getc();		/* [ */
	row_report += (UART_getc() - 0x30) * 10;	/* Row, 10's digit */
	row_report += UART_getc() - 0x30;			/* Row, 1's digit */
	UART_getc();		/* ; */
	col_report += (UART_getc() - 0x30) * 100;	/* Column, 100's digit */
	col_report += (UART_getc() - 0x30) * 10;	/* Column, 10's digit */
	col_report += UART_getc() - 0x30;			/* Column, 1's digit */	
	if( UART_getc() == 'R' )
	{
		cursor_responded = 1;	/* Put up cursor valid flag */
	}
	else
	{
		cursor_responded = 0;
	}
}

/* With Auto Linefeed on, LF, CR, FF, and vertical tab commands
cause cursor to move to first column on the next line */
void auto_linefeed_on(void)	/* unknown */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x5B);	/* [ */
	UART_putc(0x32);	/* 2 */
	UART_putc(0x30);	/* 0 */
	UART_putc(0x68);	/* h */
}
void auto_linefeed_off(void)	/* unknown */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x5B);	/* [ */
	UART_putc(0x32);	/* 2 */
	UART_putc(0x30);	/* 0 */
	UART_putc(0x6C);	/* l */
}

/* Clear all character and graphic attributes */
void clear_all_attributes(void)	/* unknown */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x5B);	/* [ */
	UART_putc(0x30);	/* 0 */
	UART_putc(0x6D);	/* m */
}

/* Reverse Video */
void reverse_video_on(void)	/* works */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x5B);	/* [ */
	UART_putc(0x37);	/* 7 */
	UART_putc(0x6D);	/* m */
}
void reverse_video_off(void)	/* works, tested by Barnett */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x5B);	/* [ */
	UART_putc(0x32);	/* 2 */
	UART_putc(0x37);	/* 7 */
	UART_putc(0x6D);	/* m */
}

/* Blinking */
void blinking_on(void)	/* works */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x5B);	/* [ */
	UART_putc(0x35);	/* 5 */
	UART_putc(0x6D);	/* m */
}
void blinking_off(void)	/* works, tested by Barnett */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x5B);	/* [ */
	UART_putc(0x32);	/* 2 */
	UART_putc(0x35);	/* 5 */
	UART_putc(0x6D);	/* m */
}

/* Reset */
/* Initialized the VFD, clears the input buffer,
the screen and all communication parameters,
and character attributes teturn to their defaults.
No characters can be sent for 900ms after the reset. */
void reset(void)	/* works */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x43);	/* C */
}

/* Character Sizes */
void single_single(void)	/* works */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x23);	/* # */
	UART_putc(0x35);	/* 5 */
}
void double_double(void)	/* works */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x23);	/* # */
	UART_putc(0x33);	/* 3 */
}

/* Digital Panel Meter Mode */
/* Display the characters to be displayed in 32x48 cell 8/
/* Example: ESC/4;+123,+010,g
   Display:	+123 +10 */
void dpmm(unsigned char a, unsigned char b, unsigned char c,
	unsigned char d, unsigned char e, unsigned char f,
	unsigned char g, unsigned char h)	/* works, tested by Barnett */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x2F);	/* / */
	UART_putc(0x34);	/* 4 */
	UART_putc(0x30+a);
	UART_putc(0x30+b);
	UART_putc(0x30+c);
	UART_putc(0x30+d);
	UART_putc(0x2C);	/* , */
	UART_putc(0x30+e);
	UART_putc(0x30+f);
	UART_putc(0x30+g);
	UART_putc(0x30+h);
	UART_putc(0x2C);	/* , */
	UART_putc(0x67);	/* g */
}

/* Brightness, 4 levels */
void brightness(unsigned char level)	/* works, tested by Barnett */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x23);	/* # */
	if( level == 1 )	/* Dimmest */
	{
		UART_putc(0x61);	/* a */
	}
	else if( level == 2 )
	{
		UART_putc(0x62);	/* b */
	}
	else if( level == 3 )
	{
		UART_putc(0x63);	/* c */
	}
	else if( level == 4 )	/* Brightest */
	{
		UART_putc(0x64);	/* d */
	}
	else	/* Default to Brightness */
	{
		UART_putc(0x64);	/* d */
	}
}

/* Self-test mode */
void self_test(void)	/* works */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x42);	/* B */
}

/* Recieved data test mode */
/* All bytes recieved will be displayed in HEX
rather than ASCII. */
void rcvd_data_test(void)	/* works */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x44);	/* D */
}
void rcvd_data_test_exit(void)	/* unknown */
{
	UART_putc(0x1B);	/* ESC */
	UART_putc(0x45);	/* E */
}

/* Cancel */
void cancel(void)	/* unknown */
{
	UART_putc(0x18);	/* CAN */
}
