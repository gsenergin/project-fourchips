/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include <p18cxxx.h>
#include "../Header Files/globalSettings.h"
#include "../Header Files/myInterruptLow.h"
#include "../Header Files/myInterruptHigh.h"

/******************************************************************
** 	    	   			COMPILER DIRECTIVES 	    		  	 **
******************************************************************/

#pragma config FOSC = INTIO67	// Internal oscillator block, port function on RA6 and RA7
#pragma config PLLCFG = OFF		// Oscillator used directly 
#pragma config PRICLKEN = OFF	// Primary clock can be disabled by software
#pragma config FCMEN = OFF		// Fail-Safe Clock Monitor disabled
#pragma config PWRTEN = ON		// Power up timer enabled
#pragma config BOREN = OFF		// Brown-out Reset disabled in hardware and software 
#pragma config WDTEN = OFF		// Watch dog timer is always disabled. SWDTEN has no effect
#pragma config LVP = OFF		// Single-Supply ICSP disabled 
#pragma config MCLRE = EXTMCLR
#pragma config IESO = OFF

#pragma code lowVector = 0x0018
void atInterruptLow (void) {
	_asm GOTO myInterruptLow _endasm
}
#pragma code

#pragma code highVector = 0x0008
void atInterruptHigh (void) {
	_asm GOTO myInterruptHigh _endasm
}
#pragma code
