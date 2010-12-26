/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	
	
	Module:	
	
	Desc.:	
**********************************************************/

#ifndef USI_H
#define USI_H
	/* USI port and pin definitions.
	 */
	#define USI_OUT_REG		PORTE	//!< USI port output register.
	#define USI_IN_REG		PINE	//!< USI port input register.
	#define USI_DIR_REG		DDRE	//!< USI port direction register.
	#define USI_CLOCK_PIN	PE4		//!< USI clock I/O pin.
	#define USI_DATAIN_PIN	PE5		//!< USI data input pin.
	#define USI_DATAOUT_PIN	PE6		//!< USI data output pin.

	/*  Speed configuration:
	 *  Bits per second = CPUSPEED / PRESCALER / (COMPAREVALUE+1) / 2.
	 *  Maximum = CPUSPEED / 64.
	 */
	#define TC0_PRESCALER_VALUE 256	//!< Must be 1, 8, 64, 256 or 1024.
	#define TC0_COMPARE_VALUE   1	//!< Must be 0 to 255. Minimum 31 with prescaler CLK/1.

	/*  Prescaler value converted to bit settings.
	 */
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
#endif