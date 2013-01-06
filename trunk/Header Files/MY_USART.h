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
 * Initializes the USART1 transmission and reception
 * with a baud rate of 9600 bauds
 */
void initUSART1 (void);

/**
 * This function writes a STRING
 */
void writeOnUSART1S (const rom char *string);

/**
 * This function writes a VARIABLE
 */
void writeOnUSART1V (char string[]);

/**
 * This function writes a CHARACTER
 */
//void writeOnUSART1C (char charactere);

/**
 * This function writes an INTEGER
 */
//void writeOnUSART1I (int integer);

#endif