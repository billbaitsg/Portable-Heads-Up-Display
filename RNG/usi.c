/***********************************************************
Bill Bai
Purdue ECET
Senior Project
Portable Heads Up Display

	Block:	Range Finder 
	
	Module:	Universal Serial Interface functions
	
	Desc.:	This file contains the source code for the USI
			functions.  This code is originally from the 
			AVR Appnote AVR319 - Using the USI module for
			SPI communications.  I have ported the code 
			over to the WinAVR compiler.
**********************************************************/

#include "proj_hdr.h"

/*! \brief  Data input register buffer.
 *
 *  Incoming bytes are stored in this byte until the next transfer is complete.
 *  This byte can be used the same way as the SPI data register in the native
 *  SPI module, which means that the byte must be read before the next transfer
 *  completes and overwrites the current value.
 */
unsigned char storedUSIDR;

/*! \brief  Driver status bit structure.
 *
 *  This struct contains status flags for the driver.
 *  The flags have the same meaning as the corresponding status flags
 *  for the native SPI module. The flags should not be changed by the user.
 *  The driver takes care of updating the flags when required.
 */
struct usidriverStatus_t {
	unsigned char masterMode : 1;       //!< True if in master mode.
	unsigned char transferComplete : 1; //!< True when transfer completed.
	unsigned char writeCollision : 1;   //!< True if put attempted during transfer.
};

volatile struct usidriverStatus_t USI_SPI_status; //!< The driver status bits.

/*! \brief  Timer/Counter 0 Compare Match Interrupt handler.
 *
 *  This interrupt handler is only enabled when transferring data
 *  in master mode. It toggles the USI clock pin, i.e. two interrupts
 *  results in one clock period on the clock pin and for the USI counter.
 */
/*#pragma vector=TIMER0_COMP_vect */	/* Compiler specific directive */
/*__interrupt void timer0comp_handler()*/
ISR(TIMER0_COMPA_vect)
{
	USICR |= (1<<USITC);	// Toggle clock output pin.
}

/* USI SPI start condition interrupt */
ISR(USI_START_vect)
{
	/* not enabled */
}

/*! \brief  USI Timer Overflow Interrupt handler.
 *
 *  This handler disables the compare match interrupt if in master mode.
 *  When the USI counter overflows, a byte has been transferred, and we
 *  have to stop the timer tick.
 *  For all modes the USIDR contents are stored and flags are updated.
 */
/*#pragma vector=USI_OVF_vect*/	/* Compiler specific directive */
/*__interrupt void usiovf_handler()*/
ISR(USI_OVF_vect)
{
	// Master must now disable the compare match interrupt
	// to prevent more USI counter clocks.
	if( USI_SPI_status.masterMode == 1 ) {
		TIMSK &= ~(1<<OCIE0A);
	}
	
	// Update flags and clear USI counter
	USISR = (1<<USIOIF);
	USI_SPI_status.transferComplete = 1;

	// Copy USIDR to buffer to prevent overwrite on next transfer.
	storedUSIDR = USIDR;
}

/*! \brief  Initialize USI as SPI master.
 *
 *  This function sets up all pin directions and module configurations.
 *  Use this function initially or when changing from slave to master mode.
 *  Note that the stored USIDR value is cleared.
 *
 *  \param spi_mode  Required SPI mode, must be 0 or 1.
 */
void USI_SPI_initmaster(void)
{
	// Configure port directions.
	USI_DIR_REG |= (1<<USI_DATAOUT_PIN) | (1<<USI_CLOCK_PIN); // Outputs.
	USI_DIR_REG &= ~(1<<USI_DATAIN_PIN);                      // Inputs.
	USI_OUT_REG |= (1<<USI_DATAIN_PIN);                       // Pull-ups.
	
	// Configure USI to 3-wire master mode with overflow interrupt.
	USICR = (1<<USIOIE) | (1<<USIWM0) |
	        (1<<USICS1) | (SPI_MODE<<USICS0) |
	        (1<<USICLK);

	// Enable 'Clear Timer on Compare match' and init prescaler.
	TCCR0A = (1<<WGM01);
	TCCR0B = TC0_PS_SETTING;
	
	// Init Output Compare Register.
	OCR0A = TC0_COMPARE_VALUE;
	
	// Init driver status register.
	USI_SPI_status.masterMode       = 1;
	USI_SPI_status.transferComplete = 0;
	USI_SPI_status.writeCollision   = 0;
	
	storedUSIDR = 0;
}

/*! \brief  Initialize USI as SPI slave.
 *
 *  This function sets up all pin directions and module configurations.
 *  Use this function initially or when changing from master to slave mode.
 *  Note that the stored USIDR value is cleared.
 *
 *  \param spi_mode  Required SPI mode, must be 0 or 1.
 */
void USI_SPI_initslave(void)
{
	// Configure port directions.
	USI_DIR_REG |= (1<<USI_DATAOUT_PIN);                      // Outputs.
	USI_DIR_REG &= ~(1<<USI_DATAIN_PIN) | (1<<USI_CLOCK_PIN) | (1<<USI_SELECT_PIN); // Inputs.
	USI_OUT_REG |= (1<<USI_DATAIN_PIN) | (1<<USI_CLOCK_PIN) | (1<<USI_SELECT_PIN);  // Pull-ups.
	
	// Configure USI to 3-wire slave mode with overflow interrupt.
	USICR = (1<<USIOIE) | (1<<USIWM0) |
	        (1<<USICS1) | (SPI_MODE<<USICS0);
	
	// Init driver status register.
	USI_SPI_status.masterMode       = 0;
	USI_SPI_status.transferComplete = 0;
	USI_SPI_status.writeCollision   = 0;
	
	storedUSIDR = 0;
}

/*! \brief  Put one byte on bus.
 *
 *  Use this function like you would write to the SPDR register in the native SPI module.
 *  Calling this function in master mode starts a transfer, while in slave mode, a
 *  byte will be prepared for the next transfer initiated by the master device.
 *  If a transfer is in progress, this function will set the write collision flag
 *  and return without altering the data registers.
 *
 *  \returns  0 if a write collision occurred, 1 otherwise.
 */
char USI_SPI_putc( unsigned char val )
{
	// Check if transmission in progress,
	// i.e. USI counter unequal to zero.
	if( (USISR & 0x0F) != 0 ) {
		// Indicate write collision and return.
		USI_SPI_status.writeCollision = 1;
		return;
	}
	
	// Reinit flags.
	USI_SPI_status.transferComplete = 0;
	USI_SPI_status.writeCollision = 0;

	// Put data in USI data register.
	USIDR = val;
	
	// Master should now enable compare match interrupts.
	if( USI_SPI_status.masterMode == 1 ) {
		TIFR |= (1<<OCF0A);   // Clear compare match flag.
		TIMSK |= (1<<OCIE0A); // Enable compare match interrupt.
	}

	if( USI_SPI_status.writeCollision == 0 ) return 1;
	return 0;
}

/*! \brief  Get one byte from bus.
 *
 *  This function only returns the previous stored USIDR value.
 *  The transfer complete flag is not checked. Use this function
 *  like you would read from the SPDR register in the native SPI module.
 */
unsigned char USI_SPI_getc(void)
{
	return storedUSIDR;
}

/*! \brief  Wait for transfer to complete.
 *
 *  This function waits until the transfer complete flag is set.
 *  Use this function like you would wait for the native SPI interrupt flag.
 */
void USI_SPI_wait(void)
{
	do {} while( USI_SPI_status.transferComplete == 0 );
}