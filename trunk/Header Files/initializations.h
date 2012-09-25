#ifndef __INITIALIZATIONS_H
#define __INITIALIZATIONS_H

/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "../Header Files/globalSettings.h"
#include "../Header Files/xlcd.h"

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

/**
 * Enable high and low interrupts
 */
void initBothPriorityInterruptGeneration (void);

/**
 * Configure the INT0 (RB0) port as INPUT and enable high priority on it
 * WARNING !!! You need to call the initBothPriorityInterruptGeneration() 
 * function once before calling this function
 */
void initINT0 (void);

/**
 * Configure the TMR1 to make an overflow each 1ms and enable high priority on it
 * WARNING !!! You need to call the initBothPriorityInterruptGeneration() 
 * function once before calling this function
 */
void initTMR1 (void);

/**
 * Configure the ADC with theses parameters :
 *		- A/D VREF+ = AVDD
 *		- A/D VREF- = AVSS
 *		- TAD = FOSC/32
 *		- TACQ = 12 TAD
 *		- Justification = RIGHT
 */
void initADC (void);

/**
 * A description of the function
 * on several lines
 *
 * @param	parameter_name	a short description of the parameter
 * @param	parameter_name	a short description of the parameter
 * @return					a short description of the return
 */
void initEUSART (void);

/**
 * Configure the ANSEL of ports used by the LCD in NUMERIC 
 * and call the OpenXLCD() function
 */
void initLCD (void);

/**
 * Used for the synchronisation with the LCD
 * Provides a 18 TCY delay
 */
void DelayFor18TCY (void);

/**
 * Used for the synchronisation with the LCD
 * Provides at least 15ms delay
 */
void DelayPORXLCD (void);

/**
 * Used for the synchronisation with the LCD
 * Provides at least 5ms delay
 */
void DelayXLCD (void);

#endif
