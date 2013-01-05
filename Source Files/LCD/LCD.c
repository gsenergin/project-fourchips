/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "LCD/LCD.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/
volatile unsigned char positionFirstSlidingString = 0;		// Used to slide a string on the first line of the LCD
volatile unsigned char positionSecondSlidingString = 0;		// Used to slide a string on the second line of the LCD

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void initLCD (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     		 INITIALIZATION OF PERIPHERALS         	  ****/
	OpenXLCD(FOUR_BIT & LINES_5X7);		// Configures I/O pins for external LCD
}

void prepareLCD (int flushStatut, int position) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
	if (flushStatut == FLUSH) {
		while(BusyXLCD());
	    WriteCmdXLCD(0x01);
	}

	if (position != AFTER) {
		while(BusyXLCD());
		SetDDRamAddr(position);
	}
}	

void writeOnLCDS (int flushStatut, int position, const rom char *string) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
	prepareLCD(flushStatut, position);
	
	while(BusyXLCD());
	putrsXLCD(string);
}

void writeOnLCDSlidingS (int flushStatut, char line, const rom char *string) {
	/****					LOCAL VARIABLES					  ****/
	unsigned char i, shift;
	
	/****     				    FUNCTION           			  ****/
	/*	How the sliding function works
	 *
	 *	The received string is associated to a variable that memorise the place
	 *	at which we have to begin to print the string.
	 *	The associated variable is positionXXXXXXSlidingString (XXX depends of sliding a string
	 *	on the first or second line.
	 *
	 *	The associated variable is incremented at each called of the function and set to 0
	 *	if it points the \0 of the string.
	 */
	
	// Prepares the LCD and sets the position of the pointer on the memorised place at which we have to begin to print the string
	if (line == 1) {
		prepareLCD(flushStatut, 0x00);
		string += positionFirstSlidingString++;
	}	
	else {
		prepareLCD(flushStatut, 0x40);
		string += positionSecondSlidingString++;
	}
	
	// A loop to write the 16 available character on the LCD or until we found a \0 on the string
	for (i = 0; (i < 16 & *(string + i) != '\0'); i++) {
		while(BusyXLCD());
		putcXLCD(*(string + i));
	}	
		
	/* 	If i is minus thant 16, it means that we have printed the string 
	 * 	or the end of the string and that we have 1 or more empty cases on the LCD line
	 */
	if (i != 16) {
		// So, we print a space between the end of the string and the beginning of the retransmitted string
		while(BusyXLCD());
		putcXLCD(' ');
		
		//We have to post-increment i and save it on the shift variable to determine the position where we have to print the next retransmitted string
		for (shift = ++i; i < 16; i++) {	
			while(BusyXLCD());
			if (line == 1)
				putcXLCD(*(string - (positionFirstSlidingString - 1) + (i - shift)));
			else
				putcXLCD(*(string - (positionSecondSlidingString - 1) + (i - shift)));
		}	
	}	
	
	// If the next character to print is a \0, we set the memorised place at which we have to begin to print the string to 0
	if (*(string + 1) == '\0') {
		if (line == 1)	
			positionFirstSlidingString = 0;
		else
			positionSecondSlidingString = 0;
	}	
}

void writeOnLCDC (int flushStatut, int position, char charactere) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
	prepareLCD(flushStatut, position);

	while(BusyXLCD());
	putcXLCD(charactere);
}

void writeOnLCDV (int flushStatut, int position, char *variable) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
	prepareLCD(flushStatut, position);

	while(BusyXLCD());
	putsXLCD(variable);
}

void writeOnLCDI (int flushStatut, int position, int entier) {
	/****					LOCAL VARIABLES					  ****/
	char string[6];
	
	/****     				    FUNCTION           			  ****/
	itoa(entier, string);	

	prepareLCD(flushStatut, position);

	while(BusyXLCD());
	putsXLCD(string);
}

void writeOnLCDF(int flushStatut, int position, float reel) {
	/****					LOCAL VARIABLES					  ****/
	char string[6];
	
	/****     				    FUNCTION           			  ****/
	
	ftoa(reel, string, 2, 'F');
	
	prepareLCD(flushStatut, position);
	
	while(BusyXLCD());
	putsXLCD(string);	
}

void DelayFor18TCY(void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
	Nop();Nop();Nop();Nop();Nop();Nop();
	Nop();Nop();Nop();Nop();Nop();Nop();
	Nop();Nop();Nop();Nop();Nop();Nop();
}

void DelayPORXLCD(void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
	Delay1KTCYx(60);
}

void DelayXLCD(void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
	Delay1KTCYx(20);
}