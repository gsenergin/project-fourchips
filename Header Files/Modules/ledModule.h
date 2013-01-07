#ifndef __LEDMODULE_H
#define __LEDMODULE_H

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
 * Call the approprate fucntion or saves the appropriate CB depending
 * of the receivedString[].
 *
 * @param	receivedString			LED code frame
 */
void clignotementLED(char receivedString[] );

/**
 * Juste switches the LED state.
 */
void clignotement(void);

#endif
