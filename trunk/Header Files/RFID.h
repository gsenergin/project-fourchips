#ifndef _RFID_H
#define _RFID_H

/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "main.h"

/******************************************************************
** 				   ENUMERATIONS - DEFINITIONS					 **
******************************************************************/

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

/**
 * Initializes the RFID module (USART2) transmission and reception
 * with a baud rate of 9600 bauds.
 */
void initRFID (void);

/**
 * The CRC value is calculated from equation x^16+x^12+x^5+1 with initial value equal to
 * 0x0000. The CRC value is calculated in virtue of all the bytes except of CRCH and CRCL.
 *
 * @param	ZAdr			the data first byte flag
 * @param	DoAdr			informs how many data bytes will be used for calculation
 * @param	Ile				is the flag for the calculated CRC value
 */
void LiczCRC2 (unsigned char *ZAdr, unsigned short *DoAdr,  unsigned char Ile); 

/**
 * Calculates and fills the CRC bytes of a writing or reading command trame
 * by calling the LicsCRC2() function.
 *
 * @param	bufRFID[]			writing of reading command trame
 */
void calculCRC (unsigned char bufRFID[9]);

/**
 * Prepares and sends a writing command trame of a specified sector
 *
 * @param	dataByte1			1st data byte to write
 * @param	dataByte2			2nd data byte to write
 * @param	dataByte3			3rd data byte to write
 * @param	dataByte4			4th data byte to write
 * @param	dataSector			data sector to modifie
 */
void RFID_Write(char dataByte1, char dataByte2, char dataByte3, char dataByte4, char dataSector);	

/**
 * Prepares and sends a reading command trame of a specified sector
 *
 * @param	dataSector			data sector to read
 */
void RFID_Read(char dataSector);	

#endif