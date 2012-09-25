#ifndef __GLOBALSETTINGS_H
#define __GLOBALSETTINGS_H

/******************************************************************
**				INCLUDES FILES (across the project)	 			 **
******************************************************************/

#include <p18cxxx.h>
#include <delays.h>
#include <stdlib.h>

/******************************************************************
** 		  ENUMERATIONS - DEFINITIONS (across the project) 	 	 **
******************************************************************/

enum {NUMERIC, ANALOGIC};		// To use with ANSEL registers [p153]
enum {OUT, IN};					// To use with TRIS registers [p155]
enum {OFF, ON};					// To use with PORT registers [p152]
enum {FLUSH, NOFLUSH, AFTER};	// To use with writeOnLCD functions

#define PORT_INT0		PORTBbits.RB0
#define TRIS_INT0		TRISBbits.TRISB0

#define PORT_LED		PORTCbits.RC2
#define TRIS_LED		TRISCbits.TRISC2

#define PORT_RELAIS		PORTBbits.RB4
#define TRIS_RELAIS		TRISBbits.TRISB4

#define INT0IFLAG		INTCONbits.INT0IF

#endif