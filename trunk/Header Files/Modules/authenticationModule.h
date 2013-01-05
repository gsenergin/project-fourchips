#ifndef __AUTHENTICATIONMODULE_H
#define __AUTHENTICATIONMODULE_H

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
 * Scans and saves the information of a RFID card (name + password).
 * If those information are found, it sends the correct info to the the program C#
 * and calls the 2nd part of the authentication process (the function waitingOfThePassword()
 * as a callback each 200ms).
 */
void getAuthentication (void);

void setNameAndPassword (const rom char *string, char code1, char code2, char code3, char code4);

/**
 * Prints a message on the LCD to enter the user's password, checks the button pressed and the loginTime.
 * If the button pressed is different than CENTER, it calls the enterCode() function to enter the button on the tableCode[] table.
 * If the button pressed is CENTER, it calls the checkCode().
 * If the loginTime arrive to 15000ms, it stops the authentication process.
 */
void waitingOfThePassword (void);

/**
 * Stores the entered button on the tableCode[] table at the correct position.
 *
 * @param	code			the button pressed (UP, DOWN, LEFT or RIGHT)
 */
void enterCode (char code);

/**
 * Checks if the tableCode[] table is completely filled (by checking if the last cell is different thant the default set value ('_').
 * If the tableCode[] table is complete, if checks if it corresponds with the tablePassword[].
 *
 * If the code is good, it sends the LOGINTRUE frame to the program C# and stops the autentication process.
 * If the code is wrong, it sends the LOGINFALSE frame to the program C#, incrementes the tryCount variable and sets the loginTime to 0.
 * If the tryCount is equal to 3, it stops the authentication process.
 */
void checkCode (void);

#endif