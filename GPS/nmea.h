/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	GPS
	
	Module:	NMEA Parser header
	
	Desc.:	This file contains the global variables and 
			function prototypes for the NMEA Parser module.
**********************************************************/

#ifndef NMEA_H
#define NMEA_H
	
	/* Function prototypes */
	unsigned char GPVTG_parser( unsigned char * );
	unsigned char GPGGA_parser( unsigned char * );
	
	/* NMEA Flag definitiongs */
	#define NMEA_RXC 1
	#define NMEA_START 2
	#define NMEA_ERROR 3

	/* NMEA Global Variables */
	extern volatile unsigned int ALTITUDE;
	extern volatile unsigned int BEARING;
	extern volatile unsigned int SPEED;
	extern volatile unsigned char HOURS;
	extern volatile unsigned char MINUTES;
	extern volatile unsigned char SECONDS;
	

	extern volatile unsigned char NMEA_SENTENCE[];
	extern volatile unsigned char NMEA_SENT_ptr;	/* NMEA Sentence pointer */
	extern volatile unsigned char NMEA_FLAGS;	/* NMEA Sentence Flags */
	extern volatile unsigned char NMEA_TYPE;

#endif
