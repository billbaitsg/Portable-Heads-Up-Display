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
	#define DD_MOSI	3
	#define DD_MISO	4
	#define DD_SCK	5
	#define DD_SSN	2

	/* SPI Function Prototypes */
	void SPI_MasterInit(void);
	void SPI_MasterTransmit(char cData);
	void SPI_SlaveInit(void);
	char SPI_SlaveReceive(void);
#endif