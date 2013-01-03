/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "INIT.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void initInterrupts (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     		INITIALIZATION OF INTERRUPTIONS           ****/
	
	/**		GENERAL		**/
	RCONbits.IPEN = 1;			// Enables priority levels on interrupts [p60]
	INTCONbits.GIE_GIEH = 1;	// Enables all high priority interrupts [p115]
	INTCONbits.PEIE_GIEL = 1;	// Enables all low priority interrupts [p115]
	
	/**		INT0		**/
	INTCONbits.INT0IF = 0;		// The INT0 external interrupt did not occur [p115]
	INTCONbits.INT0IE = 1;		// Enables the INT0 external interrupt [p115]
	INTCON2bits.INTEDG0 = 0;	// Interrupt on falling edge [p116]
	
	/**		TMR1		**/
	PIR1bits.TMR1IF = 0;		// TMR1 register did not overflow [p118]
	PIE1bits.TMR1IE = 1;		// Enables the TMR1 overflow interrupt [p123]
	IPR1bits.TMR1IP = 1;		// TMR1 overflow interrupt set to high priority [p127]

	/**		USART1_RC		**/
	PIR1bits.RC1IF = 0; // USART1 receive buffer is empty [p118]
	PIE1bits.RC1IE = 1; // Enables the USART1 receive interrupt [p123]
	IPR1bits.RC1IP = 0; // USART1 receive interrupt set to low priority [p127]
	
	/**		USART2_RC		**/
	PIR3bits.RC2IF = 0; // USART2 receive buffer is empty [p120]
	PIE3bits.RC2IE = 1; // Enables the USART2 receive interrupt [p125]
	IPR3bits.RC2IP = 1; // USART2 receive interrupt set to high priority [p129]
}