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
volatile unsigned char HALTITUDE = 7;			/* Altitude in meters */
volatile unsigned char LALTITUDE = 7;			/* Altitude in meters */
volatile unsigned char HSPEED = 8;	/* Speed in kilometers per hour */
volatile unsigned char LSPEED = 8;	/* Speed in kilometers per hour */
volatile unsigned char HBEARING = 9;	/* Bearing (Heading) of the vehicle */
volatile unsigned char LBEARING = 9;	/* Bearing (Heading) of the vehicle */
volatile unsigned char HOURS = 10;	/* Hour of the current time */
volatile unsigned char MINUTES = 11;	/* Minutes of the current hour */
volatile unsigned char SECONDS = 12;	/* Seconds of the current hour */

/* Sliding window average arrays */
//#define SLIDING
#ifdef SLIDING
	#define LENGTH 10	/* Make arrays 10 in size */
	volatile unsigned char X_ARRAY[LENGTH];
	volatile unsigned char Y_ARRAY[LENGTH];
	volatile unsigned char Z_ARRAY[LENGTH];
	volatile unsigned char R_ARRAY[LENGTH];
	volatile unsigned char L_ARRAY[LENGTH];
	volatile unsigned char ARRAY_COUNT = 0;
	/* Function Prototypes */
	unsigned char avg(unsigned char []);	/* Calculate the average of the array */
	void add(unsigned char [], unsigned char);	/* Add a new value to the array */
#endif

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

		#ifdef SLIDING
			/* Check if array counter needs to roll over */
			if( ARRAY_COUNT == LENGTH )
			{
				ARRAY_COUNT = 0;
			}
		#endif

		/* Query the Accelerometer block */
		ACC_SS_0;					/* Accelerometer slave select low (selected) */
		_delay_us(25);			/* Delay for 25 us */
			/* X-axis */
			SPI_putc('X');			/* Query ACC block for X-axis */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			_delay_us(25);			/* Delay for 25 us */
			X_AXIS = SPI_getc();	/* Read X-axis value from SPI */
			/* Y-axis */
			SPI_putc('Y');			/* Query ACC block for Y-axis */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			_delay_us(25);			/* Delay for 25 us */
			Y_AXIS = SPI_getc();	/* Read Y-axis value from SPI */
			/* Z-axis */
			SPI_putc('Z');			/* Query ACC block for Z-axis */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			_delay_us(25);			/* Delay for 25 us */
			Z_AXIS = SPI_getc();	/* Read Z-axis value from SPI */
		ACC_SS_1;					/* Accelerometer slave select high (not selected) */

		/* Query the Ambient Light block */
		AMB_SS_0;					/* Ambient slave select low (selected) */
		_delay_us(25);			/* Delay for 25 us */
			/* Light Level */
			SPI_putc('L');			/* Query AMB block for Light level */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			_delay_us(25);			/* Delay for 25 us */
			LIGHT = SPI_getc();		/* Read Light value from SPI */
		AMB_SS_1;					/* Ambient slave select high (not selected) */

		/* Query the Range block */
		RNG_SS_0;					/* Range slave select low (selected) */
		_delay_us(25);			/* Delay for 25 us */
			/* Range */
			SPI_putc('R');			/* Query RNG block for range distance */
			_delay_us(150);			/* Delay for 25 us */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			_delay_us(25);			/* Delay for 25 us */
			RANGE = SPI_getc();		/* Read Range value from SPI */
		RNG_SS_1;					/* Range slave select high (not selected) */

		#ifdef SLIDING
			ARRAY_COUNT++;	/* Increment array counter */
		#endif

		/* Query the GPS block */
		GPS_SS_0;					/* GPS slave select high (selected) */
		_delay_us(50);			/* Delay for 25 us */
			/* Altitude */
			SPI_putc('A');			/* Query GPS block for altitude */
			_delay_us(50);			/* Delay for 25 us */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			_delay_us(50);			/* Delay for 25 us */
			HALTITUDE = SPI_getc();		/* Read Altitude high byte value from SPI */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			_delay_us(50);			/* Delay for 25 us */
			LALTITUDE = SPI_getc();		/* Read Altitude low byte value from SPI */
			/* Speed */
			SPI_putc('V');			/* Query GPS block for speed */
			_delay_us(50);			/* Delay for 25 us */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			_delay_us(50);			/* Delay for 25 us */
			HSPEED = SPI_getc();		/* Read Speed high byte value from SPI */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			_delay_us(50);			/* Delay for 25 us */
			LSPEED = SPI_getc();		/* Read Speed low byte value from SPI */
			/* Bearing */
			SPI_putc('B');			/* Query GPS block for Bearing */
			_delay_us(50);			/* Delay for 25 us */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			_delay_us(50);			/* Delay for 25 us */
			HBEARING = SPI_getc();		/* Read Bearing high byte value from SPI */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			_delay_us(50);			/* Delay for 25 us */
			LBEARING = SPI_getc();		/* Read Bearing low byte value from SPI */
			/* Time */
			/* Hour */
			SPI_putc('H');			/* Query GPS block for Minutes */
			_delay_us(50);			/* Delay for 25 us */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			_delay_us(50);			/* Delay for 25 us */
			HOURS = SPI_getc();		/* Read Hours value from SPI */
			/* Minutes */
			SPI_putc('M');			/* Query GPS block for Minutes */
			_delay_us(50);			/* Delay for 25 us */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			_delay_us(50);			/* Delay for 25 us */
			MINUTES = SPI_getc();	/* Read Minutes value from SPI */
			/* Seconds */
			SPI_putc('S');			/* Query GPS block for Seconds */
			_delay_us(50);			/* Delay for 25 us */
			SPI_putc(NULL);			/* Dummy send to clock SPI */
			_delay_us(50);			/* Delay for 25 us */
			SECONDS = SPI_getc();	/* Read Seconds value from SPI */
		GPS_SS_1;	/* GPS slave select high (not selected) */

		/* Send data to Display Controller */
		#ifdef SLIDING
			/* Calculate averages */
			X_AXIS = avg(X_ARRAY);
			Y_AXIS = avg(Y_ARRAY);
			Z_AXIS = avg(Z_ARRAY);
			LIGHT = avg(L_ARRAY);
			RANGE = avg(R_ARRAY);
		#endif

		DIS_SS_0;	/* Display slave select low (selected) */
		_delay_us(25);			/* Delay for 25 us */
			/* X-axis */
			SPI_putc('x');			/* Prepare Display Controller for X-axis value */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc(X_AXIS);		/* Send X-axis value to Display Controller */
			_delay_us(25);			/* Delay for 25 us */
			/* Y-axis */
			SPI_putc('y');			/* Prepare Display Controller for Y-axis value */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc(Y_AXIS);		/* Send Y-axis value to Display Controller */
			_delay_us(25);			/* Delay for 25 us */
			/* Z-axis */
			SPI_putc('z');			/* Prepare Display Controller for Z-axis value */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc(Z_AXIS);		/* Send Z-axis value to Display Controller */
			_delay_us(25);			/* Delay for 25 us */
			/* Ambient Light */
			SPI_putc('l');			/* Prepare Display Controller for Ambient Light value */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc(LIGHT);		/* Send Ambient Light value to Display Controller */
			_delay_us(25);			/* Delay for 25 us */
			/* Range */
			SPI_putc('r');			/* Prepare Display Controller for Range value */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc(RANGE);		/* Send Range value to Display Controller */
			_delay_us(25);			/* Delay for 25 us */
			/* Altitude */
			SPI_putc('a');			/* Prepare Display Controller for Altitude value */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc( HALTITUDE );	/* Send high byte of Altitude to Display Controller */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc( LALTITUDE );		/* Send low byte of Altitude to Display Controller */
			_delay_us(25);			/* Delay for 25 us */
			/* Speed */
			SPI_putc('v');			/* Prepare Display Controller for Speed value */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc( HSPEED );		/* Send high byte of Speed to Display Controller */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc( LSPEED );			/* Send low byte of Speed to Display Controller */
			_delay_us(25);			/* Delay for 25 us */
			/* Bearing */
			SPI_putc('b');			/* Prepare Display Controller for Bearing value */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc( HBEARING );		/* Send high byte of Bearing to Display Controller */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc( LBEARING );		/* Send low byte of Bearing to Display Controller */
			_delay_us(25);			/* Delay for 25 us */
			/* Time */
			/* Hour */
			SPI_putc('h');			/* Prepare Display Controller for Hours value */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc(HOURS);		/* Send Hours value to Display Controller */
			_delay_us(25);			/* Delay for 25 us */
			/* Minutes */
			SPI_putc('m');			/* Prepare Display Controller for Minutes value */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc(MINUTES);		/* Send Minutes value to Display Controller */
			_delay_us(25);			/* Delay for 25 us */
			/* Seconds */
			SPI_putc('s');			/* Prepare Display Controller for Seconds value */
			_delay_us(25);			/* Delay for 25 us */
			SPI_putc(SECONDS);		/* Send Seconds value to Display Controller */
			_delay_us(25);			/* Delay for 25 us */
		DIS_SS_1;	/* Display slave select high (not selected) */
	}	/* End of while */
	return 0;
}	/* End of main */

#ifdef SLIDING
/* Find the average value of the array */
unsigned char avg(unsigned char array[])
{
	unsigned char avg = 0;	/* Local average variable */
	unsigned char i = 0;	/* Local counter variable */
	for(i=0;i<LENGTH;i++)
	{
		avg += array[i];	/* Sum up all items in array */
	}
	avg = (float)avg/LENGTH;	/* Divide by size of array */
	return avg;	/* Return the result */
}
#endif
