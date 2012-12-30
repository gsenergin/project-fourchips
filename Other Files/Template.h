#ifndef __ADC_H
#define __ADC_H

/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "main.h"

/******************************************************************
** 				   ENUMERATIONS - DEFINITIONS					 **
******************************************************************/

#define CANALPHOTODIODE		24		// Used as channel for ADC acquisition [p293]

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

/**
 * Initializes the ADC and configures the photodiode and ext_int
 * port with these options : TRIS = IN, ANSEL = ANALOGIC
 */
void initADC (void);

#endif