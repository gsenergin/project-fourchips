#ifndef __TIOS_H
#define __TIOS_H

/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "main.h"

/******************************************************************
** 				   ENUMERATIONS - DEFINITIONS					 **
******************************************************************/

// Defines the maximum number of callback
#define	MAX_CB		15

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

/**
 * Defines the FOSC
 * Defines all ANSELx registers in NUMERIC
 * Initializes the LED
 * Initializes the RELAY
 * Initializes the Buttons
 * Initializes the TMR1
 * Initializes the USART1
 * Initializes the RFID
 * Initializes the LCD
 * Initializes the interruptions
 * Initializes the necessary tables for callback
 */
void TIOSInitialization (void);

/**
 * Saves a callback on the callback table if there is an empty place and sets the ID callback
 *
 * @param	IDCB			ID of the callback
 * @param	functionPtr		pointer of the function to save
 * @param	CB_time			time in ms at which the function has to be recalled
 */
void TIOSSaveCB (unsigned char* IDCB, void(*functionPtr)(void), unsigned int CB_time); 

/**
 * Removes the callback on the callback table
 *
 * @param	IDCB			ID of the callback to remove
 */
void TIOSRemoveCB (unsigned char* IDCB);

/**
 * Starts the infinite loop (the OS)
 */
void TIOSStart (void);

/******************************************************************
** 	    	   	DECLARATION OF INTERRUPT ROUTINES 	    		 **
******************************************************************/

void MyInterruptHigh (void);

void MyInterruptLow (void);

#endif
