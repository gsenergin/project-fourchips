/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "Modules/serialDispatcher.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

extern unsigned char IDCB_getAuthentication;
extern char messageAuthentificationFlag;

unsigned char IDCB_serialDispatcher = 0;
volatile unsigned char receivedChar, i_receivedString = 0;

char receivedString[21] = "", EMPTY[] = "", 
	HELLO[] = "#00@",
	SCAN[] = "#01@",
	LOGINTRUE[] = "#02@1",
	LOGINFALSE[] = "#02@0",
	LOGINTIMEOUT[] = "#02@2";

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void serialDispatcher (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/	
	if (strncmp(receivedString, HELLO, 4) == 0) {
		TIOSSaveCB(&IDCB_getAuthentication, getAuthentication, 2200);
		strcpy(receivedString, EMPTY);
	}
	else if (messageAuthentificationFlag) {
		writeOnLCDS(FLUSH, 0x00, "Please login");
		writeOnLCDS(NOFLUSH, 0x40, "with RFID card");
	}		
}	