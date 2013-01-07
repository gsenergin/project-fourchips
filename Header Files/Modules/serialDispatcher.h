#ifndef __SERIALDISPATCHER_H
#define __SERIALDISPATCHER_H

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
 * This function is recalled each 200ms and manages the frame sent
 * by the C# program and calls or saves as callback the appropriate function(s)
 */
void serialDispatcher (void);

#endif