#ifndef __FTOA_H
#define __FTOA_H

/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

/******************************************************************
** 			ENUMERATIONS - DEFINITIONS (inside the file) 		 **
******************************************************************/

#define MAX_MANTISA 3

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

/**
 * Converts a float to a string
 *
 * @param	x				the float number to be converted
 * @param	str				the string in which the float will be converted
 * @param	prec			determines the digits after the point
 * @param	format			accepts only these values : 'f', 'F', 'g', 'G'
 * @return					string length
 */
int ftoa (float x, char *str, char prec, char format);

#endif