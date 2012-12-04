#ifndef __MY_USART_H
#define __MY_USART_H

/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "main.h"
#include <string.h>

/******************************************************************
** 				   ENUMERATIONS - DEFINITIONS					 **
******************************************************************/

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

/**
 * Initializes the USART transmission and reception
 * with a baud rate of 9600 bauds
 */
void initUSART (void);

void writeOnUSARTS (const rom char *string);

void writeOnUSARTV (char string[]);

void writeOnUSARTC (char charactere);

#endif