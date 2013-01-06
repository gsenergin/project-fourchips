/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "Modules/authenticationModule.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

unsigned char IDCB_getAuthentication = 0;
unsigned char IDCB_waitingOfThePassword = 0;
extern unsigned char IDCB_serialDispatcher;
extern unsigned char IDCB_Chronometre;
extern unsigned char IDCB_Clignotement_LED;
extern unsigned int elapsedMinutes;

char messageAuthentificationFlag = ON, setPasswordFlag = OFF;
extern volatile unsigned char RFID_Read_Resultat[10];
char tablePassword[4];
extern char SCAN[], LOGINTRUE[], LOGINFALSE[], LOGINTIMEOUT[], USER_CHANGE[], PW_ACK[];
int loginTime = 0;

char button = NONE, tryCount = 0;
volatile unsigned char tabCode[4] = {'_', '_', '_', '_'};	// Used to save the entered code

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/	

void getAuthentication (void) {
	/****					LOCAL VARIABLES					  ****/
	char i, tableName[20], tableDataToSend[25] , dataSector;
	
	/****     				    FUNCTION           			  ****/
	
	// Reads the sectors 1 to 5 of a RFID card and puts the result on tableName
	for (dataSector = 0x01, i = 0; dataSector < 0x06; dataSector += 0x01, i += 4) {
		RFID_Read(dataSector);
		tableName[i] = RFID_Read_Resultat[3];
		tableName[i + 1] = RFID_Read_Resultat[4];
		tableName[i + 2] = RFID_Read_Resultat[5];
		tableName[i + 3] = RFID_Read_Resultat[6];
	}
	
	// Reads the sector 6 of a RFID card and puts the result on tablePassword
	RFID_Read(dataSector);
	tablePassword[0] = RFID_Read_Resultat[3];
	tablePassword[1] = RFID_Read_Resultat[4];
	tablePassword[2] = RFID_Read_Resultat[5];
	tablePassword[3] = RFID_Read_Resultat[6];
	
	/*	DEBUG
	for (i = 0; i < 20; i++)
		writeOnUSART1C(tableName[i]);
	for (i = 0; i < 4; i++)
		writeOnUSART1C(tablePassword[i]);
	writeOnUSART1S("\n\n");
	*/
	
	/* Checks if we have the 1st byte and the last sector of the RFID card, 
	 * which certainly means that we've received the entire information we wanted
	 * and go to the the next step of the authentication process
	 */
	if (tableName[0] != 0xff && tablePassword[0] != 0xff && tablePassword[1] != 0xff && tablePassword[2] != 0xff && tablePassword[3] != 0xff) {
		// Prepares and sends the frame SCAN+Name to the C# program
		strcpy(tableDataToSend, SCAN);
		strcat(tableDataToSend, tableName);
		tableDataToSend[ strlen(tableDataToSend) ] = '\n';	// Adds a \n to the end of the frame to be correctly interpreted by the C# program
		writeOnUSART1V(tableDataToSend);
		
		// Removes the 1st step of the authentication process of the CB table
		TIOSRemoveCB(&IDCB_getAuthentication);
		
		// Sets the messageAuthentificationFlag to OFF meaning that we don't have to send an authentication message on the LCD anymore
		messageAuthentificationFlag = OFF;
		
		// Saves the 2nd step of the authentication process function as a callback
		TIOSSaveCB (&IDCB_waitingOfThePassword, waitingOfThePassword, 200);
	}
}

void setNameAndPassword (const rom char *string, char code1, char code2, char code3, char code4) {
	/****					LOCAL VARIABLES					  ****/
	char i, tableName[20], dataSector;
	
	/****     				    FUNCTION           			  ****/		
	for (i = 0; i < 20; i++)
		tableName[i] = 0xff;
		
	for(i = 0; i < 19 && *(string + i) != '\0'; i++) {
		tableName[i] = *(string + i);	// Adds the received string in tableName
		//writeOnUSART1C(tableName[i]);	// DEBUG
	}
	
	tableName[i] = '\0';	// Adds a \0 to the end of the frame to be correctly interpreted by the program
	
	// Writes the tableName on the sectors 1 to 5
	for (dataSector = 0x01, i = 0; dataSector < 0x06; dataSector += 0x01, i += 4) {
		RFID_Write(tableName[i], tableName[i + 1], tableName[i + 2], tableName[i + 3], dataSector);
	}
	
	// Writes the 4 codes on the sector 6
	RFID_Write(code1, code2, code3, code4, dataSector);
}

void setUsername (char receivedString[]) {
	/****					LOCAL VARIABLES					  ****/
	char i, tableName[20], dataSector;
	
	/****     				    FUNCTION           			  ****/	
	
	for (i = 0; i < 20; i++)
		tableName[i] = 0xff;
		
	for(i = 0; i < 19 && receivedString[i + 4] != '\0'; i++) {
		tableName[i] = receivedString[i + 4];	// Adds the received string in tableName
		//writeOnUSART1C(tableName[i]);	// DEBUG
	}
	
	tableName[i] = '\0';	// Adds a \0 to the end of the frame to be correctly interpreted by the program
	
	// Writes the tableName on the sectors 1 to 5
	for (dataSector = 0x01, i = 0; dataSector < 0x06; dataSector += 0x01, i += 4) {
		RFID_Write(tableName[i], tableName[i + 1], tableName[i + 2], tableName[i + 3], dataSector);
	}
}

void setPassword (void) {
	setPasswordFlag = ON;
	TIOSSaveCB (&IDCB_waitingOfThePassword, waitingOfThePassword, 200);
}	

void waitingOfThePassword (void) {
	/****					LOCAL VARIABLES					  ****/
	char i, tableDataToSend[7];
	
	/****     				    FUNCTION           			  ****/
	if (! setPasswordFlag)
		writeOnLCDSlidingS(FLUSH, 1, "Enter your password + button \"ENTER\"");
	else
		writeOnLCDSlidingS(FLUSH, 1, "Enter your new password + button \"ENTER\"");
	
	// Prints the entered code on the 2nd line of the LCD, if a code is entered, 
	// it shows "*", if not, it shows "_"
	prepareLCD(NOFLUSH, 0x43);
	for (i = 0; i < 4; i++) {
		if (tabCode[i] != '_')
			writeOnLCDC(NOFLUSH, AFTER, '*');
		else
			writeOnLCDC(NOFLUSH, AFTER, tabCode[i]);
		if (i < 3)
			writeOnLCDS(NOFLUSH, AFTER, "  ");
	}
	
	// Checks if a button was pressed and calls the appropriate function (and clear the button variable)
	if (button != NONE) {
		if (button != CENTER)
			enterCode(button);
		else
			checkCode();
		button = NONE;
	}
	
	if (! setPasswordFlag) {
		loginTime += 200;
	
		// If the loginTime arrive to 15000ms, it sends a "Time Out" message to the program C#,
		// sets the flag to print the authentication message on the LCD to ON and remove the callback
		if (loginTime >= 15000) {
			loginTime = 0;
			tryCount = 0;
			messageAuthentificationFlag = ON;
			//slidingStatutes();
			
			strcpy(tableDataToSend, LOGINTIMEOUT);
			tableDataToSend[ strlen(tableDataToSend) ] = '\n';
			writeOnUSART1V(tableDataToSend);
			
			TIOSRemoveCB(&IDCB_waitingOfThePassword);
		}
	}	
}

void enterCode (char code) {
	/****					LOCAL VARIABLES					  ****/
	unsigned char i;
	
	/****     				    FUNCTION           			  ****/		
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
	/****					LOCAL VARIABLES					  ****/
	char i, tableDataToSend[7];
	
	/****     				    FUNCTION           			  ****/		
	if (tabCode[3] != '_') { //Check if the code is entirely encoded
		if (! setPasswordFlag) {		
			if ((tabCode[0] == tablePassword[0]) & (tabCode[1] == tablePassword[1]) & (tabCode[2] == tablePassword[2]) & (tabCode[3] == tablePassword[3])) { //Good code entered
				strcpy(tableDataToSend, LOGINTRUE);
				TIOSRemoveCB(&IDCB_waitingOfThePassword);
				TIOSSaveCB(&IDCB_Chronometre, chronometre, 60000);
				messageAuthentificationFlag = OFF;
			}	
			else { //Wrong code entered
				strcpy(tableDataToSend, LOGINFALSE);
				
				tryCount++;
				
				// If the user fails to login 3 times, it stop the authentication procedure
				if (tryCount == 3) {
					tryCount = 0;
					TIOSRemoveCB(&IDCB_waitingOfThePassword);
					messageAuthentificationFlag = ON;
				}	
			}
			
			loginTime = 0; // Resets the loginTime to allow new 15000ms to re-enter a code
		}
		else {
			strcpy(tableDataToSend, PW_ACK);
			// Writes the 4 codes on the sector 6
			RFID_Write(tabCode[0], tabCode[1], tabCode[2], tabCode[3], 0x06);
			
			TIOSRemoveCB(&IDCB_waitingOfThePassword);
		}	
		
		// Cleans the tabCode table
		for (i = 0; i < 4; i++)
			tabCode[i] = '_';
		
		tableDataToSend[ strlen(tableDataToSend) ] = '\n';
		writeOnUSART1V(tableDataToSend);
	}
}	

void logoff (void) {
	unsigned char i, tempIDCB;
	
	for(i = 1; i < MAX_CB; i++) {
		if (i != IDCB_serialDispatcher)
			tempIDCB = i;
			TIOSRemoveCB(&tempIDCB);
	}
	
	messageAuthentificationFlag = ON;
	setPasswordFlag = OFF;
	loginTime = 0;
	button = NONE;
	tryCount = 0;
	
	PORT_LED = OFF;
	elapsedMinutes = 0;
	
	setIP_ADDR((192ul), (168ul), (1ul), (200ul));
	setMASK((255ul), (255ul), (255ul), (0ul));
	setGATEWAY((192ul), (168ul), (1ul), (254ul));
	setPRIMARY_DNS((8ul), (8ul), (8ul), (8ul));
	setSECONDARY_DNS((8ul), (8ul), (4ul), (4ul));
}	