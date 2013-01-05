/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "Modules/ethernetModule.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

unsigned char IDCB_stackUpdate = 0;
extern char CARD_IP[], CARD_NETWORK[], CARD_GW[], CARD_DNS1[], CARD_DNS2[];

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void stackUpdate (void) {
	StackTask();
	StackApplications();
}

void updateCardNIC (char receivedString[]) {
	char i, bit, receivedBYTES[16], receivedBYTE1[4], receivedBYTE2[4], receivedBYTE3[4], receivedBYTE4[4];
	unsigned long BYTE1, BYTE2, BYTE3, BYTE4;
	
	for (i = 0; i < 19 && receivedString[i] != '\0'; i++) {
		receivedBYTES[i] = receivedString[i + 4];
	}
	
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
	
	receivedBYTE1[ strlen(receivedBYTE1) ] = '\0';
	receivedBYTE2[ strlen(receivedBYTE1) ] = '\0';
	receivedBYTE3[ strlen(receivedBYTE1) ] = '\0';
	receivedBYTE4[ strlen(receivedBYTE1) ] = '\0';
	
	BYTE1 = (unsigned long)atoi(receivedBYTE1);
	
	/*	DEBUG
	writeOnUSART1V(receivedBYTE1);
	writeOnUSART1V(receivedBYTE2);
	writeOnUSART1V(receivedBYTE3);
	writeOnUSART1V(receivedBYTE4);
	*/
	
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