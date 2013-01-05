#ifndef __CHRONO_H
#define __CHRONO_H

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
 * Initializes the ADC and configures the photodiode and ext_int
 * port with these options : TRIS = IN, ANSEL = ANALOGIC
 */
void chronometre(void);

#endif