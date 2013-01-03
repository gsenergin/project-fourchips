/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "RFID.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

volatile unsigned char RFID_Write_Flag = OFF;
volatile unsigned char RFID_Read_Flag = OFF;
volatile unsigned char RFID_i = 0;
volatile unsigned char RFID_Read_Resultat[10];

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void initRFID (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     		 INITIALIZATION OF PERIPHERALS         	  ****/
	TRISDbits.TRISD6 = IN;		// Configures RD6 (TX2) in OUTPUT (write) [p155]
	TRISDbits.TRISD7 = IN;		// Configures RD7 (RX2) in INPUT (read) [p155]

	TXSTA2bits.TXEN=1; 		// Transmit enabled [p274][optional]
	RCSTA2bits.SPEN=1; 		// Serial port enabled [p275][optional]
	RCSTA2bits.CREN = 1;
	
	TXSTA2bits.SYNC = 0;		// Asynchronous mode [p274]
	TXSTA2bits.BRGH=0;			// Low speed [p274]
	BAUDCON2bits.BRG16 = 1;		// 16-bit Baud Rate Generator is used [p276]
	
	/*	Because we are on asynchronous mode (SYNC = 0), low speed (BRGH = 0)
	 *	and that we use a 16-bit baud rate generator, we have to use the following formula : [p277]
	 *	FOSC / (16 * (n + 1))	where n = (FOSC / (16 * Desired BaudRate)) -1
	 *	So, n = ( 16MHz / (16 * 9600) ) - 1 = 103,17 (we only keep the decimal part)
	 *	Calculated BaudRate = 16MHz / (16 * (103 + 1)) = 9615,38 (we only keep the decimal part)
	 *
	 *	We have to put n (103 = 0x67) in [SPBREGH1:SPBRG1] registers
	 */
	SPBRGH2 = 0x00;
	SPBRG2 = 0x67;
}

void LiczCRC2 (unsigned char *ZAdr, unsigned short *DoAdr,  unsigned char Ile) {
int     i,NrBajtu; 
 unsigned short C; 
        *DoAdr=0; 
        for (NrBajtu=1;NrBajtu<=Ile;NrBajtu++,ZAdr++) 
        { 
                C=((*DoAdr>>8)^*ZAdr)<<8; 
                for (i=0;i<8;i++) 
                        if (C&0x8000) C=(C<<1)^0x1021; 
                        else C=C<<1; 
                *DoAdr=C^(*DoAdr<<8); 
        } 
}  

void calculCRC (unsigned char bufRFID[9]) {
	unsigned char tempBufRFID;
	
	if (bufRFID[2] == 0x10) { // Case of Writing
		LiczCRC2(bufRFID, (unsigned short *)&bufRFID[9], 9);
		
		tempBufRFID = bufRFID[9];
		bufRFID[9] = bufRFID[10];
		bufRFID[10] = tempBufRFID;
	}	
	else if (bufRFID[2] == 0x12) { // Case of Reading
		LiczCRC2(bufRFID, (unsigned short *)&bufRFID[4], 4);
		
		tempBufRFID = bufRFID[4];
		bufRFID[4] = bufRFID[5];
		bufRFID[5] = tempBufRFID;
	}
}	

void RFID_Write(char dataByte1, char dataByte2, char dataByte3, char dataByte4, char dataSector) {
	unsigned char i, bufRFID[11];
	
	/*	bufRFID[0] = Module Address
	 *	bufRFID[1] = Frame length
	 *	bufRFID[2] = Command
	 *	bufRFID[3] = Data (byte 1)
	 *	bufRFID[4] = Data (byte 2)
	 *	bufRFID[5] = Data (byte 3)
	 *	bufRFID[6] = Data (byte 4)
	 *	bufRFID[7] = Data Sector
	 *	bufRFID[8] = Lock Statut
	 *	bufRFID[9] = CRCH
	 *	bufRFID[10] = CRCL
	 */
	
	bufRFID[0] = 0xff;
	bufRFID[1] = 0x0b;
	bufRFID[2] = 0x10;
	bufRFID[3] = dataByte1;
	bufRFID[4] = dataByte2;
	bufRFID[5] = dataByte3;
	bufRFID[6] = dataByte4;
	bufRFID[7] = dataSector;
	bufRFID[8] = 0x00;
	
	calculCRC(bufRFID);
	
	while(RFID_Write_Flag);
	while(RFID_Read_Flag);
	
	RFID_i = 0;
	RFID_Write_Flag = ON;
	
	for (i = 0; i < 11; i++) {
		while (!TXSTA2bits.TRMT);	
		TXREG2 = bufRFID[i];	// Buffer filling [p275]
	}
	
	while(RFID_Write_Flag);
	
//	writeOnUSART1V((char)bufRFID);	
}	

void RFID_Read(char dataSector) {
	unsigned char i, bufRFID[6];
	
	bufRFID[0] = 0xff;
	bufRFID[1] = 0x06;
	bufRFID[2] = 0x12;
	bufRFID[3] = dataSector;
	
	calculCRC(bufRFID);
	
	while(RFID_Write_Flag);
	while(RFID_Read_Flag);
	
	RFID_i = 0;
	RFID_Read_Flag = ON;
	
	for (i = 0; i < 6; i++) {
		while (!TXSTA2bits.TRMT);	
		TXREG2 = bufRFID[i];	// Buffer filling [p275]
	}
	
	while(RFID_Read_Flag);
	
	/*
	for (i = 0; i < 10; i++) {
		writeOnUSART1I(RFID_Read_Resultat[i]);
	}
	*/
}