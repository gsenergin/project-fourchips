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

char receivedString[21] = " ", EMPTY[] = " ", 
	HELLO[] = "#00@",
	SCAN[] = "#01@",
	LOGINTRUE[] = "#02@1",
	LOGINFALSE[] = "#02@0",
	LOGINTIMEOUT[] = "#02@2",
	CARD_IP[] = "#31@",
	CARD_NETWORK[] = "#32@",
	CARD_GW[] = "#33@",
	CARD_DNS1[] = "#34@",
	CARD_DNS2[] = "#35@",
	LED[] = "#06@";

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void serialDispatcher (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/	
	if (receivedString[4] == '\0' || receivedString[5] == '\0') {
		if (strncmp(receivedString, HELLO, 4) == 0) {
			//TIOSSaveCB(&IDCB_getAuthentication, getAuthentication, 2200);
			writeOnUSART1S("#01@Arnaud Helin\n");
			Delay10KTCYx(255);
			writeOnUSART1S("#02@1\n");
			strcpy(receivedString, EMPTY);
		}
		else if ((strncmp(receivedString, CARD_IP, 4) == 0) ||
			(strncmp(receivedString, CARD_NETWORK, 4) == 0) ||
			(strncmp(receivedString, CARD_GW, 4) == 0) ||
			(strncmp(receivedString, CARD_DNS1, 4) == 0) ||
			(strncmp(receivedString, CARD_DNS2, 4) == 0)) {
			updateCardNIC(receivedString);
			strcpy(receivedString, EMPTY);
		}
		else if (strncmp(receivedString, LED, 4) == 0) {
			clignotementLED(receivedString);
			strcpy(receivedString, EMPTY);
		}
		
		if (messageAuthentificationFlag) {
			writeOnLCDS(FLUSH, 0x00, "Please login");
			writeOnLCDS(NOFLUSH, 0x40, "with RFID card");
		}
	}	
	PORT_RELAY ^= ON;
}	