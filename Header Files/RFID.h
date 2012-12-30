#ifndef _RFID_H
#define _RFID_H

// INCLUDE (si applicable)

#include "main.h"

// DEFINE


//D�finit le tampon de r�ception maximal RFID
#define MAXBUFRFID				11 





// VALEURS CORRESPONDANTS AUX COMMANDES DU RFID




/* D�claration des fonctions */
void LiczCRC2(unsigned char *ZAdr, unsigned short *DoAdr,  unsigned char Ile);

void calculCRC (unsigned char bufRFID[9]);

void writeOnRFIDW(char dataByte1, char dataByte2, char dataByte3, char dataByte4, char dataSector);

void writeOnRFIDR(char dataSector);

void initRFID ();


#endif /* _RFID_H */
