/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "MY_USART.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void initUSART (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     		 INITIALIZATION OF PERIPHERALS         	  ****/
	TRISCbits.TRISC6 = OUT;		// Configures RC6 (TX1) in OUTPUT (write) [p155]
	TRISCbits.TRISC7 = IN;		// Configures RC7 (RX1) in INPUT (read) [p155]

	TXSTA1bits.TXEN=1; 		// Transmit enabled [p274][optional]
	RCSTA1bits.SPEN=1; 		// Serial port enabled [p275][optional]
	
	TXSTA1bits.SYNC = 0;		// Asynchronous mode [p274]
	TXSTA1bits.BRGH=0;			// Low speed [p274]
	BAUDCON1bits.BRG16 = 1;		// 16-bit Baud Rate Generator is used [p276]
	
	/*	Because we are on asynchronous mode (SYNC = 0), low speed (BRGH = 0)
	 *	and that we use a 16-bit baud rate generator, we have to use the following formula : [p277]
	 *	FOSC / (16 * (n + 1))	where n = (FOSC / (16 * Desired BaudRate)) -1
	 *	So, n = ( 16MHz / (16 * 9600) ) - 1 = 103,17 (we only keep the decimal part)
	 *	Calculated BaudRate = 16MHz / (16 * (103 + 1)) = 9615,38 (we only keep the decimal part)
	 *
	 *	We have to put n (103 = 0x67) in [SPBREGH1:SPBRG1] registers
	 */
	SPBRGH1 = 0x00;
	SPBRG1 = 0x67;
}

void writeOnUSARTS (const rom char *string) {
	/****					LOCAL VARIABLES					  ****/
	unsigned int i;
	
	/****     				    FUNCTION           			  ****/	
	for(i = 0; *(string + i) != '\0'; i++) {
		/*	Wait that the Transmit Shift Register Status bit pass to 1, 
		 *  meaning that TSR is empty [p274]
		 */
		while (!TXSTA1bits.TRMT);	
		TXREG1 = *(string + i);	// Buffer filling [p275]
	}
}

void writeOnUSARTV (char string[]) {
	/****					LOCAL VARIABLES					  ****/
	unsigned int i;
	
	/****     				    FUNCTION           			  ****/	
	for(i = 0; i < strlen(string); i++) {
		/*	Wait that the Transmit Shift Register Status bit pass to 1, 
		 *  meaning that TSR is empty [p274]
		 */
		while (!TXSTA1bits.TRMT);	
		TXREG1 = string[i];	// Buffer filling [p275]
	}
}

void writeOnUSARTC (char charactere) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/	
	while (!TXSTA1bits.TRMT);	
	TXREG1 = charactere;	// Buffer filling [p275]
}