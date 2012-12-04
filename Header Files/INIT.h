#ifndef __INIT_H
#define __INIT_H

/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "main.h"

/******************************************************************
** 				   ENUMERATIONS - DEFINITIONS					 **
******************************************************************/

#define INT0IFLAG	INTCONbits.INT0IF	// Flag of INT0 [p115]
#define TMR1IFLAG	PIR1bits.TMR1IF		// Flag of TMR1 [p118]
#define RC1IFLAG	PIR1bits.RC1IF		// Flag of EUSART_RC [p118]

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

/**
 * Enables the high and low priorities
 * Enables the high priority on TMR1
 * Enables the low priority on EUSART on reception
 */
void initInterrupts (void);

#endif