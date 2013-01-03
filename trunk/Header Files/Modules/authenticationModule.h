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

void getAuthentication (void);

void setNameAndPassword (const rom char *string, char code1, char code2, char code3, char code4);

void waitingOfThePassword (void);

void enterCode (char code);

void checkCode (void);

#endif