#include "../Header Files/writeOnLCD.h"

/******************************************************************
** 			ENUMERATIONS - DEFINITIONS (inside the file) 		 **
******************************************************************/

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

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
