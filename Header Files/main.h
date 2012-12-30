#ifndef __MAIN_H
#define __MAIN_H

/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include <p18cxxx.h>
#include <string.h>
#include <delays.h>
#include "INIT.h"
#include "TIOS.h"
#include "TIMERS.h"
#include "ADC.h"
#include "MY_USART.h"
#include "LCD/LCD.h"
#include "1WIRE.h"
#include "ETHERNET/MyEthernet.h"
#include "RFID.h"

/******************************************************************
** 					ENUMERATIONS - DEFINITIONS					 **
******************************************************************/

enum {OFF, ON};
enum {OUT, IN};
enum {NUMERIC, ANALOGIC};
enum {FALSE, TRUE};

enum {NOFLUSH, FLUSH, AFTER};					// Used on writeOnLCDx functions
enum {OFF, ON, CLI_2SEC, CLI_1SEC};				// Used with the actionOnLED variable
enum {NONE, UP, DOWN, LEFT, CENTER, RIGHT};		// Used with the button variable

#define PORT_INT0	PORTBbits.RB0		// [p152]
#define TRIS_INT0	TRISBbits.TRISB0	// [p155]

#define PORT_CENTER	PORTCbits.RC0		// [p152]
#define	TRIS_CENTER	TRISCbits.TRISC0	// [p155]

#define PORT_RIGHT	PORTCbits.RC1		// [p152]
#define	TRIS_RIGHT	TRISCbits.TRISC1	// [p155]

#define PORT_LED	PORTCbits.RC2		// [p152]
#define TRIS_LED	TRISCbits.TRISC2	// [p155]

#define PORT_DOWN	PORTEbits.RE0		// [p152]
#define TRIS_DOWN	TRISEbits.TRISE0	// [p155]

#define PORT_LEFT	PORTEbits.RE1		// [p152]
#define TRIS_LEFT	TRISEbits.TRISE1	// [p155]

#define PORT_UP		PORTEbits.RE2		// [p152]
#define TRIS_UP		TRISEbits.TRISE2	// [p155]

#define PORT_RELAY	PORTBbits.RB4		// [p152]
#define TRIS_RELAY	TRISBbits.TRISB4	// [p155]

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

void main (void);

#endif