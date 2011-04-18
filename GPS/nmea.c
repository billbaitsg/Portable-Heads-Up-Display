/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	GPS
	
	Module:	NMEA Parser functions
	
	Desc.:	This file contains the source code for the
			functions for the NMEA Parser module.
**********************************************************/

#include "proj_hdr.h"

/* Global Variables */
/* NMEA sentence buffer of max size 82 chars */
//volatile unsigned char NMEA_SENTENCE[82];
//volatile unsigned char NMEA_SENT_ptr = 0;	/* NMEA Sentence pointer */
//volatile unsigned char NMEA_FLAGS = 0;	/* NMEA Sentence Flags */
volatile unsigned char NMEA_TYPE = 0;
/* NMEA Types:
	0 - No type
	1 - GPGGA, Global Position System Fix Data
	2 - GPGLL, Latitude/Longitude
	3 - GPGSA, GNSS DOP and Active Satellites 
	4 - GPGSV, GNSS Satellites in View
	5 - GPRMC, Recommended Minimum Specific GNSS Data
	6 - GPVTG, Course Over Ground and Ground Speed */

volatile unsigned int ALTITUDE = 0;//13579;
volatile unsigned int BEARING = 2436;
volatile unsigned int SPEED = 0;//12345;
volatile unsigned char HOURS = 12;
volatile unsigned char MINUTES = 30;
volatile unsigned char SECONDS = 45;

/* GPS data parser for the GPVTG sentence */
/* Parses for Bearing and Speed in kmh */
//unsigned char GPVTG_parser( unsigned char * sentence )
//{
//	/* Local Variables */
//	unsigned char ack = 0;
//
//	/* Parser */
//	ack = sscanf(sentence, "$GPVTG,%f,T,,M,%*f,n,%f,k,%*c*%*2c\r\n", &BEARING, &SPEED);
//
//	return ack;
//}
//
///* GPS data parser for the GPGGA sentence */
///* Parses for Hours, Minutes, Seconds, and Altitude in meters */
//unsigned char GPGGA_parser( unsigned char * sentence )
//{
//	/* Local Variables */
//	unsigned char ack = 0;
//
//	/* Parser */
//	ack = sscanf(sentence, "$GPGGA,%2d%2d%2d.%*3d,%*f,%*c,%*f,%*c,%*d,%8d,%*f,%f,M,,,,%*d*%*2c\r\n",
//					&HOURS, &MINUTES, &SECONDS, &ALTITUDE);
//
//	return ack;
//}
