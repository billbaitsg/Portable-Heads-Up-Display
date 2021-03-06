/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Main Controller

	Module:	SPI bus functions
	
	Desc.:	This file contains the source code for the SPI
			bus functions
**********************************************************/

#include "proj_hdr.h"

/* Initialize SPI for master mode */
void SPI_MasterInit(void)
{
	/* Configure SSn, MOSI, and SCK as output */
	DDR_SPI |= (1<<DD_MOSI)|(1<<DD_SCK)|(1<<DD_SSN);
	/* Configure MISO as input */
	DDR_SPI &= ~(1<<DD_MISO);
	/* Set MISO pull up resistor */
	PORT_SPI |= (1<<DD_MISO);
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
}

/* Recieve a byte of data via the SPI bus in slave mode */
char SPI_getc(void)
{
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)))
	;
	/* Return Data Register */
	return SPDR;
}
