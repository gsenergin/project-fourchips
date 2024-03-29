/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "Modules/serialDispatcher.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

extern unsigned char IDCB_getAuthentication;
extern unsigned char messageAuthentificationFlag;

extern unsigned char IDCB_serialDispatcher;
volatile unsigned char receivedChar, i_receivedString = 0;

char receivedString[25] = " ", EMPTY[] = " ", 
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
	TEMP[] = "#04@",
	LED[] = "#06@",
	USER_CHANGE[] = "#81@",
	PW_CHANGE[] = "#82@",
	PW_ACK[] = "#82@",
	GOODBYE[] = "#99@";
	
/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void serialDispatcher (void) {
	/****					LOCAL VARIABLES					  ****/
	char i;
	
	/****     				    FUNCTION           			  ****/
	for (i = 4; i < 25 && receivedString[i] != '\0'; i++); // Checks if a \0 is present on receivedString (because it is necessary for the strncmp function later)
	if (i < 25 && receivedString[0] == '#' && receivedString[3] == '@') { // If i is minus than 25, a /0 is present on receivedString, then after, it checks if the first character is # ad the 4th is @
		if (strncmp(receivedString, HELLO, 4) == 0) {
			TIOSSaveCB(&IDCB_getAuthentication, getAuthentication, 2200);
		}
		else if ((strncmp(receivedString, CARD_IP, 4) == 0) ||
			(strncmp(receivedString, CARD_NETWORK, 4) == 0) ||
			(strncmp(receivedString, CARD_GW, 4) == 0) ||
			(strncmp(receivedString, CARD_DNS1, 4) == 0) ||
			(strncmp(receivedString, CARD_DNS2, 4) == 0)) {
			updateCardNIC(receivedString);
		}
		else if (strncmp(receivedString, LED, 4) == 0) {
			clignotementLED(receivedString);
		}
		else if (strncmp(receivedString, USER_CHANGE, 4) == 0) {
			setUsername(receivedString);
		}
		else if (strncmp(receivedString, PW_CHANGE, 4) == 0) {
			setPassword();
		}
		else if (strncmp(receivedString, GOODBYE, 4) == 0) {
			logoff();
		}
		
		strcpy(receivedString, EMPTY);		
	}
	
	if (messageAuthentificationFlag) {
		writeOnLCDS(FLUSH, 0x00, "Please login");
		writeOnLCDS(NOFLUSH, 0x40, "with RFID card");
	}
	
	/* 	This instruction switches the Relay each time the serialDispatcher function ends, 
	 * 	because of our presumed problem of memory, if the program is still running,
	 * 	we'll listen the relay continually switches
	 */
	PORT_RELAY ^= ON;	
}	