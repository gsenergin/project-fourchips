#ifndef __LCD_H
#define __LCD_H

/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include <stdlib.h>
#include <delays.h>
#include "LCD/xlcd.h"
#include "ftoa.h"

/******************************************************************
** 				   ENUMERATIONS - DEFINITIONS					 **
******************************************************************/

enum {NOFLUSH, FLUSH, AFTER};

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

/**
 * Initializes the LCD with these options : FOUR_BIT, LINES_5X7,
 * DON, CURSOR_OFF, BLINK_OFF and positions the cursor at 0x00
 */
void initLCD (void);

/**
 * This function is called by all the writeOnLCDx() functions
 * It determines how the screen and the cursor should be prepared
 *
 * @param	flushStatut	if it is FLUSH, the screen is erased, 
 *						else, NOFLUSH does nothing
 * @param	position	if it is AFTER, the position of the cursor doesn't change
 *						else, set the cursor to the position (in hex)
 */
void prepareLCD (int flushStatut, int position);

/**
 * This function call the prepareLCD() function and write a STRING
 *
 * @param	flushStatut	if it is FLUSH, the screen is erased, 
 *						else, NOFLUSH does nothing
 * @param	position	if it is AFTER, the position of the cursor doesn't change
 * 						else, set the cursor to the position (in hex)
 */
void writeOnLCDS (int flushStatut, int position, const rom char *string);

/**
 * This function is used to slide a STRING on a specified line
 *
 * ATTENTION : You have to call this function many times to make the "sliding effect"
 *
 * @param	flushStatut	if it is FLUSH, the screen is erased, 
 *						else, NOFLUSH does nothing
 * @param	line		if it is 1, the STRING will slide on the 1st line of the LCD
 *						else, the STRING will slide on the 2nd line of the LCD
 */
void writeOnLCDSlidingS (int flushStatut, char line, const rom char *string);
//void writeOnLCDSlidingV (int flushStatut, char line, char *variable);

/**
 * This function call the prepareLCD() function and write a CHARACTER
 *
 * @param	flushStatut	if it is FLUSH, the screen is erased, 
 *						else, NOFLUSH does nothing
 * @param	position	if it is AFTER, the position of the cursor doesn't change
 * 						else, set the cursor to the position (in hex)
 */
void writeOnLCDC (int flushStatut, int position, char charactere);

/**
 * This function call the prepareLCD() function and write a VARIABLE
 *
 * @param	flushStatut	if it is FLUSH, the screen is erased, 
 *						else, NOFLUSH does nothing
 * @param	position	if it is AFTER, the position of the cursor doesn't change
 * 						else, set the cursor to the position (in hex)
 */
//void writeOnLCDV (int flushStatut, int position, char *variable);

/**
 * This function call the prepareLCD() function and write an INTEGER
 *
 * @param	flushStatut	if it is FLUSH, the screen is erased, 
 						else, NOFLUSH does nothing
 * @param	position	if it is AFTER, the position of the cursor doesn't change
  						else, set the cursor to the position (in hex)
 */
//void writeOnLCDI (int flushStatut, int position, int entier);

/**
 * This function call the prepareLCD() function and write a FLOAT
 *
 * @param	flushStatut	if it is FLUSH, the screen is erased, 
 						else, NOFLUSH does nothing
 * @param	position	if it is AFTER, the position of the cursor doesn't change
  						else, set the cursor to the position (in hex)
 */
//void writeOnLCDF(int flushStatut, int position, float reel);

/**
 * Provides a 18 TCY delay
 */
void DelayFor18TCY(void);

/**
 * Provides at least 15ms delay
 */
void DelayPORXLCD(void);

/**
 * Provides at least 5ms delay
 */
void DelayXLCD(void);

#endif