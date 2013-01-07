/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "Modules/ethernetModule.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

extern char CARD_IP[], CARD_NETWORK[], CARD_GW[], CARD_DNS1[], CARD_DNS2[];

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void stackUpdate (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
	StackTask();
	StackApplications();
}

void updateCardNIC (char receivedString[]) {
	/****					LOCAL VARIABLES					  ****/
	char i, bit, receivedBYTES[16], receivedBYTE1[4], receivedBYTE2[4], receivedBYTE3[4], receivedBYTE4[4];
	unsigned long BYTE1, BYTE2, BYTE3, BYTE4;
	
	/****     				    FUNCTION           			  ****/
	
	// This loop removes the code from the receivedString and copy the received bytes.
	// Exemple : if we have received #31@192.168.1.1, 192.168.1.1 is copied on receivedBYTES
	for (i = 0; i < 19 && receivedString[i] != '\0'; i++) {
		receivedBYTES[i] = receivedString[i + 4];
	}
	
	// The 4 next loops removes the point between each byte and copy each byte on a separate string.
	// Exemple : if we have 192.168.1.1, 192 is copied on receivedBYTE1; 162 is copied on receivedBYTE2; ...
	for (i = 0, bit = 0; receivedBYTES[i] != '.'; i++, bit++) {
		receivedBYTE1[bit] = receivedBYTES[i];
	}
	
	for (i++, bit = 0; receivedBYTES[i] != '.'; i++, bit++) {
		receivedBYTE2[bit] = receivedBYTES[i];
	}
	
	for (i++, bit = 0; receivedBYTES[i] != '.'; i++, bit++) {
		receivedBYTE3[bit] = receivedBYTES[i];
	}
	
	for (i++, bit = 0; receivedBYTES[i] != '\0'; i++, bit++) {
		receivedBYTE4[bit] = receivedBYTES[i];
	}
	
	// A \0 is added at the end of the string to be correctly interpretted for the next function strtoul
	receivedBYTE1[ strlen(receivedBYTE1) ] = '\0';
	receivedBYTE2[ strlen(receivedBYTE1) ] = '\0';
	receivedBYTE3[ strlen(receivedBYTE1) ] = '\0';
	receivedBYTE4[ strlen(receivedBYTE1) ] = '\0';
	
	// Converts the string into a unsigned long (this type is necessary to be correctly interpretted for AppConfig function
	BYTE1 = strtoul(receivedBYTE1, NULL, 10);
	BYTE2 = strtoul(receivedBYTE2, NULL, 10);
	BYTE3 = strtoul(receivedBYTE3, NULL, 10);
	BYTE4 = strtoul(receivedBYTE4, NULL, 10);
	
	/*	//DEBUG
	writeOnUSART1V(receivedBYTE1);
	writeOnUSART1V(receivedBYTE2);
	writeOnUSART1V(receivedBYTE3);
	writeOnUSART1V(receivedBYTE4);
	*/
	
	// Calls the appropriate function depending on the received code
	if (strncmp(receivedString, CARD_IP, 4) == 0) {
		setIP_ADDR(BYTE1, BYTE2, BYTE3, BYTE4);
	}
	else if (strncmp(receivedString, CARD_NETWORK, 4) == 0) {
		setMASK(BYTE1, BYTE2, BYTE3, BYTE4);
	}
	else if (strncmp(receivedString, CARD_GW, 4) == 0) {
		setGATEWAY(BYTE1, BYTE2, BYTE3, BYTE4);
	}
	else if (strncmp(receivedString, CARD_DNS1, 4) == 0) {
		setPRIMARY_DNS(BYTE1, BYTE2, BYTE3, BYTE4);
	}
	else if (strncmp(receivedString, CARD_DNS2, 4) == 0) {
		setSECONDARY_DNS(BYTE1, BYTE2, BYTE3, BYTE4);
	}
}	