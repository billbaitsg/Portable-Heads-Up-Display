/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Main Controller

	Module:	SPI bus header
	
	Desc.:	This file contains the function prototype and
			variable definitions for the SPI bus functions
**********************************************************/

#ifndef SPI_H
#define SPI_H
	/* SPI Defines */
	#define DDR_SPI	DDRB
	#define DD_MOSI	0
	#define DD_MISO	1
	#define DD_SCK	2
	#define DD_SSN	3

	/* SPI Function Prototypes */
	void SPI_MasterInit(void);
	void SPI_MasterTransmit(char cData);
	void SPI_SlaveInit(void);
	char SPI_SlaveReceive(void);
#endif