#ifndef __WRITEONLCD_H
#define __WRITEONLCD_H

/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "../Header Files/globalSettings.h"
#include "../Header Files/xlcd.h"

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

/**
 * This function is called by all the writeOnLCDx() functions
 * It determines how the screen and the cursor should be prepared
 *
 * @param	flushStatut	if it is FLUSH, the screen is erased, 
 						else, NOFLUSH does nothing
 * @param	position	if it is AFTER, the position of the cursor doesn't change
 						else, set the cursor to the position (in hex)
 */
void prepareLCD (int flushStatut, int position);

/**
 * This function call the prepareLCD() function and write a STRING
 *
 * @param	flushStatut	if it is FLUSH, the screen is erased, 
 						else, NOFLUSH does nothing
 * @param	position	if it is AFTER, the position of the cursor doesn't change
  						else, set the cursor to the position (in hex)
 */
void writeOnLCDS (int flushStatut, int position, const rom char *string);

/**
 * This function call the prepareLCD() function and write a CHARACTER
 *
 * @param	flushStatut	if it is FLUSH, the screen is erased, 
 						else, NOFLUSH does nothing
 * @param	position	if it is AFTER, the position of the cursor doesn't change
  						else, set the cursor to the position (in hex)
 */
void writeOnLCDC (int flushStatut, int position, char charactere);

/**
 * This function call the prepareLCD() function and write a VARIABLE
 *
 * @param	flushStatut	if it is FLUSH, the screen is erased, 
 						else, NOFLUSH does nothing
 * @param	position	if it is AFTER, the position of the cursor doesn't change
  						else, set the cursor to the position (in hex)
 */
void writeOnLCDV (int flushStatut, int position, char *variable);

/**
 * This function call the prepareLCD() function and write an INTEGER
 *
 * @param	flushStatut	if it is FLUSH, the screen is erased, 
 						else, NOFLUSH does nothing
 * @param	position	if it is AFTER, the position of the cursor doesn't change
  						else, set the cursor to the position (in hex)
 */
void writeOnLCDI (int flushStatut, int position, int entier);

#endif
