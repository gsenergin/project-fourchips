/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "Modules/authenticationModule.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

unsigned char IDCB_getAuthentication = 0;
unsigned char IDCB_waitingOfThePassword = 0;

char messageAuthentificationFlag = ON;
extern volatile unsigned char RFID_Read_Resultat[10];
char tablePassword[4];
extern char SCAN[], LOGINTRUE[], LOGINFALSE[], LOGINTIMEOUT[];
int loginTime = 0;

char button = NONE, tryCount = 0;
volatile unsigned char positionEntrerCodeMessage = 0;		// Used to slide the enterCodeMessage
volatile unsigned char tabCode[4] = {'_', '_', '_', '_'};	// Used to save the entered code

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/	

void getAuthentication (void) {
	char i, tableName[20], tableDataToSend[25] , dataSector;
	PORT_RELAY ^= ON;
	for (dataSector = 0x01, i = 0; dataSector < 0x06; dataSector += 0x01, i += 4) {
		RFID_Read(dataSector);
		tableName[i] = RFID_Read_Resultat[3];
		tableName[i + 1] = RFID_Read_Resultat[4];
		tableName[i + 2] = RFID_Read_Resultat[5];
		tableName[i + 3] = RFID_Read_Resultat[6];
	}
	
	RFID_Read(dataSector);
	tablePassword[0] = RFID_Read_Resultat[3];
	tablePassword[1] = RFID_Read_Resultat[4];
	tablePassword[2] = RFID_Read_Resultat[5];
	tablePassword[3] = RFID_Read_Resultat[6];
	
	/*
	for (i = 0; i < 20; i++)
		writeOnUSART1C(tableName[i]);
	for (i = 0; i < 4; i++)
		writeOnUSART1C(tablePassword[i]);
	writeOnUSART1S("\n\n");
	*/
	
	if (tableName[0] != 0xff && tablePassword[0] != 0xff && tablePassword[1] != 0xff && tablePassword[2] != 0xff && tablePassword[3] != 0xff) {
		strcpy(tableDataToSend, SCAN);
		strcat(tableDataToSend, tableName);
		tableDataToSend[ strlen(tableDataToSend) ] = '\n';
		writeOnUSART1V(tableDataToSend);
		TIOSRetirerCB_TIMER(&IDCB_getAuthentication);
		messageAuthentificationFlag = OFF;
		TIOSSaveCallBack (&IDCB_waitingOfThePassword, waitingOfThePassword, 200);
	}
}

void setNameAndPassword (const rom char *string, char code1, char code2, char code3, char code4) {
	char i, tableName[20], dataSector;
	
	for (i = 0; i < 20; i++)
		tableName[i] = 0xff;
		
	for(i = 0; *(string + i) != '\0' && i < 20; i++) {
		tableName[i] = *(string + i);
		//writeOnUSART1C(tableName[i]);
	}
	
	tableName[i] = '\0';
	
	for (dataSector = 0x01, i = 0; dataSector < 0x06; dataSector += 0x01, i += 4) {
		RFID_Write(tableName[i], tableName[i + 1], tableName[i + 2], tableName[i + 3], dataSector);
	}
	
	RFID_Write(code1, code2, code3, code4, dataSector);
}

void waitingOfThePassword (void) {
	unsigned char i, shift;
	char message[] = "Enter your password + button \"ENTER\"", tableDataToSend[7];
	unsigned char* ptrString = message;
	
	ptrString += positionEntrerCodeMessage++;
	
	prepareLCD(FLUSH, 0x00);
	
	for (i = 0; (i < 16 & *(ptrString + i) != '\0'); i++)
		writeOnLCDC(NOFLUSH, AFTER, *(ptrString + i));
		
	if (i != 16) {
		writeOnLCDC(NOFLUSH, AFTER, ' ');
		for (shift = ++i; i < 16; i++)
			writeOnLCDC(NOFLUSH, AFTER, *(ptrString - (positionEntrerCodeMessage - 1) + (i - shift)));
	}	
	
	if (*(ptrString + 1) == '\0')
		positionEntrerCodeMessage = 0;
		
	prepareLCD(NOFLUSH, 0x43);
	
	for (i = 0; i < 4; i++) {
		if (tabCode[i] != '_')
			writeOnLCDC(NOFLUSH, AFTER, '*');
		else
			writeOnLCDC(NOFLUSH, AFTER, tabCode[i]);
		if (i < 3)
			writeOnLCDS(NOFLUSH, AFTER, "  ");
	}
	
	if (button != NONE) {
		if (button != CENTER)
			enterCode(button);
		else
			checkCode();
		button = NONE;
	}
	
	loginTime += 200;
	
	if (loginTime >= 15000) {
		loginTime = 0;
		tryCount = 0;
		messageAuthentificationFlag = ON;
		
		strcpy(tableDataToSend, LOGINTIMEOUT);
		tableDataToSend[ strlen(tableDataToSend) ] = '\n';
		writeOnUSART1V(tableDataToSend);
		
		TIOSRetirerCB_TIMER(&IDCB_waitingOfThePassword);
	}	
}

void enterCode (char code) {
	unsigned char i;
	
	// Searches a place in the tabCode[] to save the code
	for (i = 0; i < 4 & tabCode[i] != '_'; i++);
	
	if (i < 4) { // If a place is found
		switch (code) {
		case UP:
			tabCode[i] = UP;
			break;
		case DOWN:
			tabCode[i] = DOWN;
			break;
		case LEFT:
			tabCode[i] = LEFT;
			break;
		case RIGHT:	
			tabCode[i] = RIGHT;
			break;
		}		
	}
}

void checkCode (void) {
	char i, tableDataToSend[7];
	
	if (tabCode[3] != '_') { //Check if the code is entirely encoded		
		if ((tabCode[0] == tablePassword[0]) & (tabCode[1] == tablePassword[1]) & (tabCode[2] == tablePassword[2]) & (tabCode[3] == tablePassword[3])) { //Good code entered
			strcpy(tableDataToSend, LOGINTRUE);
			TIOSRetirerCB_TIMER(&IDCB_waitingOfThePassword);
		}	
		else { //Wrong code entered
			strcpy(tableDataToSend, LOGINFALSE);
			
			for (i = 0; i < 4; i++)
				tabCode[i] = '_';
			
			tryCount++;
			if (tryCount == 3) {
				tryCount = 0;
				TIOSRetirerCB_TIMER(&IDCB_waitingOfThePassword);
				messageAuthentificationFlag = ON;
			}	
		}
		
		tableDataToSend[ strlen(tableDataToSend) ] = '\n';
		writeOnUSART1V(tableDataToSend);
		
		loginTime = 0;
	}
}	