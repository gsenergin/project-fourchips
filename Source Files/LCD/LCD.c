/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "LCD/LCD.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void initLCD (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     		 INITIALIZATION OF PERIPHERALS         	  ****/
	OpenXLCD(FOUR_BIT & LINES_5X7);		// Configures I/O pins for external LCD
}

void prepareLCD (int flushStatut, int position) {
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
	prepareLCD(flushStatut, position);
	
	while(BusyXLCD());
	putrsXLCD(string);
}

void writeOnLCDC (int flushStatut, int position, char charactere) {
	prepareLCD(flushStatut, position);

	while(BusyXLCD());
	putcXLCD(charactere);
}

void writeOnLCDV (int flushStatut, int position, char *variable) {
	prepareLCD(flushStatut, position);

	while(BusyXLCD());
	putsXLCD(variable);
}

void writeOnLCDI (int flushStatut, int position, int entier) {
	char string[6];
	
	itoa(entier, string);	

	prepareLCD(flushStatut, position);

	while(BusyXLCD());
	putsXLCD(string);
}

void writeOnLCDF(int flushStatut, int position, float reel) {
	char string[6];
	
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