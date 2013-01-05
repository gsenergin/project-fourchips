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
#define TMR0IFLAG	INTCONbits.TMR0IF
#define TMR1IFLAG	PIR1bits.TMR1IF		// Flag of TMR1 [p118]
#define USART1IFLAG	PIR1bits.RC1IF		// Flag of USART1_RC [p118]
#define RFIDIFLAG	PIR3bits.RC2IF		// Flag of USART2_RC [p120]

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

/**
 * Enables the high and low priorities
 * Enables the high priority on INT0 (falling edge)
 * Enables the high priority on TMR1
 * Enables the low priority on USART1 on reception
 * Enables the high priority on USART2 on reception (RFID)
 */
void initInterrupts (void);

#endif