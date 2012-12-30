#include "RFID.h"



// Variables


// Déclaration des fonctions internes
volatile unsigned char RFID_Read_Falg = OFF;
volatile unsigned char RFID_i;
volatile unsigned char RFID_Read_Resultat[4];

// Contenu des fonctions

//Calculs du CRC RFID (voir datasheet Q5M)
void LiczCRC2(unsigned char *ZAdr, unsigned short *DoAdr,  unsigned char Ile) 
{ 
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
	unsigned char i;
	
	if (bufRFID[2] == 0x10) { //Ecriture
		LiczCRC2(bufRFID, (unsigned short *)&bufRFID[9], 9);
		
		i = bufRFID[9];
		bufRFID[9] = bufRFID[10];
		bufRFID[10] = i;
	}	
	else if (bufRFID[2] == 0x12) { //Lecture
		LiczCRC2(bufRFID, (unsigned short *)&bufRFID[4], 4);
		
		i = bufRFID[4];
		bufRFID[4] = bufRFID[5];
		bufRFID[5] = i;
	}	
	
	
}	

void writeOnRFIDW(char dataByte1, char dataByte2, char dataByte3, char dataByte4, char dataSector) {
	unsigned char i, bufRFID[11];
	
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
	
	writeOnLCDI(NOFLUSH, 0x00, bufRFID[9]);
	writeOnLCDS(NOFLUSH, AFTER, " - ");
	writeOnLCDI(NOFLUSH, AFTER, bufRFID[10]);
}	

void writeOnRFIDR(char dataSector) {
	unsigned char i, bufRFID[6];
	
	bufRFID[0] = 0xff;
	bufRFID[1] = 0x06;
	bufRFID[2] = 0x12;
	bufRFID[3] = dataSector;
	
	calculCRC(bufRFID);
	
	//writeOnLCDI(NOFLUSH, 0x40, bufRFID[4]);
	//writeOnLCDS(NOFLUSH, AFTER, " - ");
	//writeOnLCDI(NOFLUSH, AFTER, bufRFID[5]);
	
	RFID_Read_Falg = ON;
	RFID_i = 0;
	
	
	prepareLCD(FLUSH, 0x00);
	
	
	for (i = 0; i < 6; i++) {
		writeOnLCDI(NOFLUSH, AFTER, bufRFID[i]);
		//while (!TXSTA2bits.TRMT);	
			TXREG2 = bufRFID[i];	// Buffer filling [p275]
		writeOnLCDS(NOFLUSH, AFTER, " ");
		if (i == 2)
			prepareLCD(NOFLUSH, 0x40);
	}
	
	while(RFID_Read_Falg);
	prepareLCD(FLUSH, 0x00);
	for (i = 0; i < 4; i++) {
		writeOnLCDI(NOFLUSH, AFTER, RFID_Read_Resultat[i]);
		writeOnLCDS(NOFLUSH, AFTER, " ");
		if (i == 1)
			prepareLCD(NOFLUSH, 0x40);
	}	
}	

void initRFID () {
	/****					LOCAL VARIABLES					  ****/
	
	/****     		 INITIALIZATION OF PERIPHERALS         	  ****/
	TRISDbits.TRISD6 = OUT;		// Configures RD6 (TX2) in OUTPUT (write) [p155]
	TRISDbits.TRISD7 = IN;		// Configures RD7 (RX2) in INPUT (read) [p155]

	TXSTA2bits.TXEN=1; 		// Transmit enabled [p274][optional]
	RCSTA2bits.SPEN=1; 		// Serial port enabled [p275][optional]
	
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