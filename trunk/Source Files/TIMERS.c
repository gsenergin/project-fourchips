/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "TIMERS.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void initTMR1 (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     		 INITIALIZATION OF PERIPHERALS         	  ****/
	T1CONbits.TMR1ON = 1;			// Enables Timer1 [p172]
	T1CONbits.TMR1CS = 0b00;		// Timer1 clock source is instruction clock (FOSC/4) [p172]
	T1CONbits.T1CKPS = 0b11;		// Timer1 input clock prescale 1:8 [p172]
	T1GCONbits.TMR1GE = 0;			// Timer1 counts regardless of Timer1 gate function [p173]

	/*	TMR1 Incrementation Time = FOSC/4/8 = 2µs
	 *	We want the TMR1 to be on overflow each 1ms, so we need 1ms/2µs (500) incrementations
	 *	We have to configure the pair registers to ((2^16)-1) - 500 = (65536-1) - 500 = 65035 = 0xFE0B
	 */
	TMR1H = 0xFE;
	TMR1L = 0x0B;	
}
