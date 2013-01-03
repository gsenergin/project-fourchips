#ifndef _RFID_H
#define _RFID_H

/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "main.h"

/******************************************************************
** 				   ENUMERATIONS - DEFINITIONS					 **
******************************************************************/

#define MAXBUFRFID				11 

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

void initRFID (void);

void LiczCRC2 (unsigned char *ZAdr, unsigned short *DoAdr,  unsigned char Ile); 

void calculCRC (unsigned char bufRFID[9]);

void RFID_Write(char dataByte1, char dataByte2, char dataByte3, char dataByte4, char dataSector);	

void RFID_Read(char dataSector);	

#endif