#ifndef __1WIRE_H
#define __1WIRE_H

/******************************************************************
**                                                INCLUDES FILES                                                 **
******************************************************************/

#include "main.h"

/******************************************************************
**                                 ENUMERATIONS - DEFINITIONS                                    **
******************************************************************/

#define DQ_LOW                  TRISBbits.TRISB5 = OUT; PORTBbits.RB5 = OFF
#define DQ_RELEASE              TRISBbits.TRISB5 = IN
#define DQ_READ                 PORTBbits.RB5

/******************************************************************
**                                FUNCTION PROTOTYPES                                    **
******************************************************************/

/**
 * Initializes the communication with the DS18B20
 *
 * @return                                      0 if the initialization is done
 */
int OWInit (void);

/**
 * Writes a bit on DQ
 *
 * @param       bit                             bit to send
 */
void OWWriteBit (int bit);

/**
 * Reads a bit on DQ and returns it
 *
 * @return                                      bit read
 */
int OWReadBit (void);

/**
 * Writes a byte on DQ (using the OWWriteBit() function)
 *
 * @param       byte                    byte to send
 */
void OWWriteByte (int byte);

/**
 * Reads a byte on DQ and returns it
 *
 * @return                                      byte read
 */
int OWReadByte (void);

/**
 * Starts a conversion of the temperature on DS18B20
 * Using OWInit() function and skipping the ROM
 *
 * ATTENTION !!! You have to provide a 750ms delay between
 * calling this function and the Read_Temperature() function
 */
void Convert_Temperature (void);

/**
 * Start a reading of the temperature on DS18B20
 * Using OWInit() function and skipping the ROM
 *
 * ATTENTION !! You have to call the Convert_Temperature() function
 * at least 750ms before calling this function
 *
 * @return                                      converted temperature in °C
 */
float Read_Temperature (void);

#endif