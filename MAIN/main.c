/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Main Controller
	
	Module:	Main program
	
	Desc.:	This is the main program section of the 
			Main microcontroller
**********************************************************/

#include "proj_hdr.h"	/* Include project header file */

/* Global Variables */
/* Accelerometer variables */
volatile unsigned char X_AXIS = 2;	/* X-axis acceleration */
volatile unsigned char Y_AXIS = 3;	/* Y-axis acceleration */
volatile unsigned char Z_AXIS = 4;	/* Z-axis acceleration */
/* Range Finder variables */
volatile unsigned char RANGE = 5;	/* Range finder distance */
/* Ambient Light variables */
volatile unsigned char LIGHT = 6;	/* Ambient light level */
/* GPS variables */
volatile int ALTITUDE = 7;			/* Altitude in meters */
volatile unsigned int SPEED = 8;	/* Speed in kilometers per hour */
volatile unsigned int BEARING = 9;	/* Bearing (Heading) of the vehicle */
volatile unsigned char HOURS = 10;	/* Hour of the current time */
volatile unsigned char MINUTES = 11;	/* Minutes of the current hour */
volatile unsigned char SECONDS = 12;	/* Seconds of the current hour */

int main(void)
{
	/* Local Variables */
	unsigned char hbyte = 0;	/* Upper byte */
	unsigned char lbyte = 0;	/* Lower byte */
	
	/* Initialize software modules */
	SPI_MasterInit();	/* Initialize SPI */
	
	/* I/O Initialization */
	DDRD = 0xFF;	/* Set PortD outputs */
	
	/* Set all slave selects to high (not selected) */
	ACC_SS_1;	/* Accelerometer slave select high (not selected) */
	GPS_SS_1;	/* GPS slave select high (not selected) */
	AMB_SS_1;	/* Ambient slave select high (not selected) */
	RNG_SS_1;	/* Range slave select high (not selected) */
	DIS_SS_1;	/* Display slave select high (not selected) */	
	
	sei();	/* Enable global interrupts */
	
	while(1)
	{
		/* Query the sensor blocks for sensor data */
		/* Query the Accelerometer block */
		ACC_SS_0;					/* Accelerometer slave select low (selected) */
			/* X-axis */
			SPI_putc('X');			/* Query ACC block for X-axis */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			X_AXIS = SPI_getc();	/* Read X-axis value from SPI */
			/* Y-axis */
			SPI_putc('Y');			/* Query ACC block for Y-axis */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			Y_AXIS = SPI_getc();	/* Read Y-axis value from SPI */
			/* Z-axis */
			SPI_putc('Z');			/* Query ACC block for Z-axis */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			Z_AXIS = SPI_getc();	/* Read Z-axis value from SPI */
		ACC_SS_1;					/* Accelerometer slave select high (not selected) */
		
		/* Query the Ambient Light block */
		AMB_SS_0;					/* Ambient slave select low (selected) */
			/* Light Level */
			SPI_putc('L');			/* Query AMB block for Light level */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			LIGHT = SPI_getc();		/* Read Light value from SPI */
		AMB_SS_1;					/* Ambient slave select high (not selected) */
		
		/* Query the Range block */
		RNG_SS_0;					/* Range slave select low (selected) */
			/* Range */
			SPI_putc('R');			/* Query RNG block for range distance */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			RANGE = SPI_getc();		/* Read Range value from SPI */
		RNG_SS_1;					/* Range slave select high (not selected) */
		
		/* Query the GPS block */
		GPS_SS_0;					/* GPS slave select high (selected) */
			/* Altitude */
			SPI_putc('A');			/* Query GPS block for altitude */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			hbyte = SPI_getc();		/* Read Altitude high byte value from SPI */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			lbyte = SPI_getc();		/* Read Altitude low byte value from SPI */
			ALTITUDE = (hbyte<<8) & lbyte;	/* Save Altitude value */
			/* Speed */
			SPI_putc('V');			/* Query GPS block for speed */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			hbyte = SPI_getc();		/* Read Speed high byte value from SPI */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			lbyte = SPI_getc();		/* Read Speed low byte value from SPI */
			SPEED = (hbyte<<8) & lbyte;	/* Save Speed value */
			/* Bearing */
			SPI_putc('B');			/* Query GPS block for Bearing */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			hbyte = SPI_getc();		/* Read Bearing high byte value from SPI */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			lbyte = SPI_getc();		/* Read Bearing low byte value from SPI */
			BEARING = (hbyte<<8) & lbyte;	/* Save Heading value */
			/* Time */
			/* Hour */
			SPI_putc('H');			/* Query GPS block for Minutes */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			HOURS = SPI_getc();		/* Read Hours value from SPI */
			/* Minutes */
			SPI_putc('M');			/* Query GPS block for Minutes */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			MINUTES = SPI_getc();	/* Read Minutes value from SPI */
			/* Seconds */
			SPI_putc('S');			/* Query GPS block for Seconds */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			SECONDS = SPI_getc();	/* Read Seconds value from SPI */			
		GPS_SS_1;	/* GPS slave select high (not selected) */
		
		/* Send data to Display Controller */
		DIS_SS_0;	/* Display slave select low (selected) */
			/* X-axis */
			SPI_putc('x');			/* Prepare Display Controller for X-axis value */
			SPI_putc(X_AXIS);		/* Send X-axis value to Display Controller */
			/* Y-axis */
			SPI_putc('y');			/* Prepare Display Controller for Y-axis value */
			SPI_putc(Y_AXIS);		/* Send Y-axis value to Display Controller */
			/* Z-axis */
			SPI_putc('z');			/* Prepare Display Controller for Z-axis value */
			SPI_putc(Z_AXIS);		/* Send Z-axis value to Display Controller */
			/* Ambient Light */
			SPI_putc('l');			/* Prepare Display Controller for Ambient Light value */
			SPI_putc(LIGHT);		/* Send Ambient Light value to Display Controller */
			/* Range */
			SPI_putc('r');			/* Prepare Display Controller for Range value */
			SPI_putc(RANGE);		/* Send Range value to Display Controller */
			/* Altitude */
			SPI_putc('a');			/* Prepare Display Controller for Altitude value */
			SPI_putc( (char)(ALTITUDE>>8) );	/* Send high byte of Altitude to Display Controller */
			SPI_putc( (char)(ALTITUDE) );		/* Send low byte of Altitude to Display Controller */
			/* Speed */
			SPI_putc('v');			/* Prepare Display Controller for Speed value */
			SPI_putc( (char)(SPEED>>8) );		/* Send high byte of Speed to Display Controller */
			SPI_putc( (char)(SPEED) );			/* Send low byte of Speed to Display Controller */
			/* Bearing */
			SPI_putc('b');			/* Prepare Display Controller for Bearing value */
			SPI_putc( (char)(BEARING>>8) );		/* Send high byte of Bearing to Display Controller */
			SPI_putc( (char)(BEARING) );		/* Send low byte of Bearing to Display Controller */
			/* Time */
			/* Hour */
			SPI_putc('h');			/* Prepare Display Controller for Hours value */
			SPI_putc(HOURS);		/* Send Hours value to Display Controller */
			/* Minutes */
			SPI_putc('m');			/* Prepare Display Controller for Minutes value */
			SPI_putc(MINUTES);		/* Send Minutes value to Display Controller */
			/* Seconds */
			SPI_putc('s');			/* Prepare Display Controller for Seconds value */
			SPI_putc(SECONDS);		/* Send Seconds value to Display Controller */
		DIS_SS_1;	/* Display slave select high (not selected) */	
	}	/* End of while */
	return 0;
}	/* End of main */