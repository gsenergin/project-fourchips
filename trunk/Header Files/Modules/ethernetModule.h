#ifndef __ETHERNETMODULE_H
#define __ETHERNETMODULE_H

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
 * Calls the StackTask() and StackApplications() functions.
 * This function is called on the TIOSStart() loop.
 */
void stackUpdate (void);

/**
 * Modify the ethernet parameter depending on the receivedString.
 *
 * @param	receivedString			the code + the IP information to change
 */
void updateCardNIC (char receivedString[]);

#endif