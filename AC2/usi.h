/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Accelerometer Microcontroller 2
	
	Module:	Universal Serial Interface header
	
	Desc.:	This file contains the global variables for 
			the USI	functions.  This code is originally 
			from the AVR Appnote AVR319 - Using the USI 
			module for SPI communications.  I have ported 
			the code over to the WinAVR compiler.
**********************************************************/

#ifndef USI_H
#define USI_H
	/* Set SPI bus mode */
	#define SPI_MODE 0	/* Sample on leading _rising_ edge, setup on trailing _falling_ edge. */
	//#define SPI_MODE 1	/* Sample on leading _falling_ edge, setup on trailing _rising_ edge. */

	/* USI port and pin definitions. */
	#define USI_OUT_REG		PORTB	//!< USI port output register.
	#define USI_IN_REG		PINB	//!< USI port input register.
	#define USI_DIR_REG		DDRB	//!< USI port direction register.
	#define USI_CLOCK_PIN	2		//!< USI clock I/O pin.
	#define USI_SELECT_PIN	0
	#define USI_DATAIN_PIN	0		//!< USI data input pin.
	#define USI_DATAOUT_PIN	1		//!< USI data output pin.

	/*  Speed configuration:
	 *  Bits per second = CPUSPEED / PRESCALER / (COMPAREVALUE+1) / 2.
	 *  Maximum = CPUSPEED / 64.
	 *	8MHz / 64 = 125kHz
	 *	125kHz = 8MHz / 8 / (3+1) / 2
	 *	Prescaler = 8
	 *	Compare Value = 3
	 */
	#define TC0_PRESCALER_VALUE 8	//!< Must be 1, 8, 64, 256 or 1024.
	#define TC0_COMPARE_VALUE   3	//!< Must be 0 to 255. Minimum 31 with prescaler CLK/1.

	/*  Prescaler value converted to bit settings. */
	#if TC0_PRESCALER_VALUE == 1
		#define TC0_PS_SETTING (1<<CS00)
	#elif TC0_PRESCALER_VALUE == 8
		#define TC0_PS_SETTING (1<<CS01)
	#elif TC0_PRESCALER_VALUE == 64
		#define TC0_PS_SETTING (1<<CS01)|(1<<CS00)
	#elif TC0_PRESCALER_VALUE == 256
		#define TC0_PS_SETTING (1<<CS02)
	#elif TC0_PRESCALER_VALUE == 1024
		#define TC0_PS_SETTING (1<<CS02)|(1<<CS00)
	#else
		#error Invalid T/C0 prescaler setting.
	#endif
	
	/* Function Prototypes */
	ISR(TIMER0_COMPA_vect);
	ISR(USI_START_vect);
	ISR(USI_OVF_vect);
	void USI_SPI_initmaster(void);
	void USI_SPI_initslave(void);
	char USI_SPI_putc(unsigned char);
	unsigned char USI_SPI_getc(void);
	void USI_SPI_wait(void);
#endif