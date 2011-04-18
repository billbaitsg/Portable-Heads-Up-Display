/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Display Controller

	Module:	SPI bus functions
	
	Desc.:	This file contains the source code for the SPI
			bus functions
**********************************************************/

#include "proj_hdr.h"

/* Initialize SPI for master mode */
void SPI_MasterInit(void)
{
	/* Cofigure SSn, MOSI, and SCK as output */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SSN);
	/* Set SPE and MSTR of the SPCR register */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);
	/* Clear SPI Interrupt Flag by reading SPSR and SPDR */
	char read;
	read = SPSR;
	read = SPDR;
}

/* Transmit a byte of data via the SPI bus in master mode */
void SPI_putc(char cData)
{
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}

/* Initialize the SPI for slave mode */
void SPI_SlaveInit(void)
{
	/* Set MISO output, all others input */
	DDR_SPI = (1<<DD_MISO);
	/* Enable SPI */
	SPCR = (1<<SPIE)|(1<<SPE);
	/* Clear SPI Interrupt Flag by reading SPSR and SPDR */
	char read;
	read = SPSR;
	read = SPDR;
}

/* Recieve a byte of data via the SPI bus in slave mode */
char SPI_getc(void)
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));
	/* Return Data Register */
	return SPDR;
}

volatile unsigned char cnt = 0;		/* Recieve byte counter */
volatile unsigned char type = 0;	/* Type of byte recieved */
ISR(SPI_STC_vect)
{
	/* Local Variables */
	unsigned char rcv = 0;
		
	rcv = SPDR;	/* Get SPI Data Register value */
	if( cnt == 0 )
	{
		if( rcv == 'x' )	/* if the X-axis is sent */
		{
			cnt = 1;
			type = 1;
		}
		else if( rcv == 'y' )	/* if the Y-axis is sent */
		{
			cnt = 1;
			type = 2;
		}
		else if( rcv == 'z' )	/* if the Z-axis is sent */
		{
			cnt = 1;
			type = 3;
		}
		else if( rcv == 'l' )	/* if the Ambient Light level is sent */
		{
			cnt = 1;
			type = 4;
		}
		else if( rcv == 'r' )	/* if the Range distance is sent */
		{
			cnt = 1;
			type = 5;
		}
		else if( rcv == 'a' )	/* if the Altitude is sent */
		{
			cnt = 2;
			type = 6;
		}
		else if( rcv == 'v' )	/* if the Speed is sent */
		{
			cnt = 2;
			type = 7;
		}
		else if( rcv == 'b' )	/* if the Bearing is sent */
		{
			cnt = 2;
			type = 8;
		}
		else if( rcv == 'h' )	/* if the Hours are sent */
		{
			cnt = 1;
			type = 9;
		}
		else if( rcv == 'm' )	/* if the Minutes are sent */
		{
			cnt = 1;
			type = 10;
		}
		else if( rcv == 's' )	/* if the Hours are sent */
		{
			cnt = 1;
			type = 11;
		}
		else	/* all other requests, do nothing */
		{
			cnt = 0;
			type = 0;
		}
	}
	else if( cnt == 1 )
	{
		if( type == 1 )			/* if the X-axis is sent */
		{
			X_AXIS = SPDR;		/* Get X-axis value from the Main Controller */
			cnt = 0;
			type = 0;
		}
		else if( type == 2 )	/* if the Y-axis is sent */
		{
			Y_AXIS = SPDR;		/* Get Y-axis value from the Main Controller */
			cnt = 0;
			type = 0;
		}
		else if( type == 3 )	/* if the Z-axis is sent */
		{
			Z_AXIS = SPDR;		/* Get Z-axis value from the Main Controller */
			cnt = 0;
			type = 0;
		}
		else if( type == 4 )	/* if the Ambient Light level is sent */
		{
			LIGHT = SPDR;		/* Get Ambient Light value from the Main Controller */
			cnt = 0;
			type = 0;
		}
		else if( type == 5 )	/* if the Range distance is sent */
		{
			RANGE = SPDR;		/* Get Range value from the Main Controller */
			cnt = 0;
			type = 0;
		}
		else if( type == 6 )	/* if the Altitude is sent */
		{
			ALTITUDE += SPDR;	/* Low byte of Altitude */
			cnt = 0;
			type = 0;
		}
		else if( type == 7 )	/* if the Speed is sent */
		{
			SPEED += SPDR;		/* Low byte of Speed */
			cnt = 0;
			type = 0;
		}
		else if( type == 8 )	/* if the Bearing is sent */
		{
			BEARING += SPDR;	/* Low byte of Bearing */
			cnt = 0;
			type = 0;
		}
		else if( type == 9 )	/* if the Hours are sent */
		{
			HOURS = SPDR;		/* Get Hours value from the Main Controller */
			cnt = 0;
			type = 0;
		}
		else if( type == 10 )	/* if the Minutes are sent */
		{
			MINUTES = SPDR;		/* Get Minutes value from the Main Controller */
			cnt = 0;
			type = 0;
		}
		else if( type == 11 )	/* if the Seconds are sent */
		{
			SECONDS = SPDR;		/* Get Seconds value from the Main Controller */
			cnt = 0;
			type = 0;
		}
		else	/* all other requests, do nothing */
		{
			cnt = 0;
			type = 0;
		}
	}
	else if( cnt == 2 )
	{
		if( type == 6 )	/* if the Altitude is sent */
		{
			ALTITUDE = 0;	/* reset Altitude */
			ALTITUDE += (SPDR<<8);	/* High byte of Altitude */
			cnt = 1;
			type = 6;
		}
		else if( type == 7 )	/* if the Speed is sent */
		{
			SPEED = 0;	/* reset SPEED */
			SPEED += (SPDR<<8) ;	/* High byte of Speed */
			cnt = 1;
			type = 7;
		}
		else if( type == 8 )	/* if the Bearing is sent */
		{
			BEARING = 0;	/* reset BEARING */
			BEARING += (SPDR<<8);	/* High byte of Bearing */
			cnt = 1;
			type = 8;
		}
		else
		{
			cnt = 0;
			type = 0;
		}
	}
	else
	{
		cnt = 0;
		type = 0;
	}
}
