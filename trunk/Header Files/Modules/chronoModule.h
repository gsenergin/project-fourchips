#ifndef __CHRONOMODULE_H
#define __CHRONOMODULE_H

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
 * This function is called each 60000ms and increments a value that determine
 * the connection time of the user.
 * This time is converted in a format : #07@hh;mm and sent to the C# program.
 */
void chronometre(void);

#endif