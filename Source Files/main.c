/*********************************************************************************************************
**							Electronic programming of microcontroller in C								**
**																										**
**									Developed by MALHERBE Lionel										**
**																										**
*********************************************************************************************************/

/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "main.h"

/******************************************************************
** 	    	   			COMPILER DIRECTIVES 	    		  	 **
******************************************************************/

#pragma config FOSC = INTIO67		// Internal oscillator block, port function on RA6 and RA7
#pragma config PLLCFG = OFF			// Oscillator used directly 
#pragma config PRICLKEN = OFF		// Primary clock can be disabled by software
#pragma config FCMEN = OFF			// Fail-Safe Clock Monitor disabled
#pragma config PWRTEN = ON			// Power up timer enabled
#pragma config BOREN = OFF			// Brown-out Reset disabled in hardware and software 
#pragma config WDTEN = OFF			// Watch dog timer is always disabled. SWDTEN has no effect
#pragma config LVP = OFF			// Single-Supply ICSP disabled 
#pragma config MCLRE = EXTMCLR		// MCLR pin enabled, RE3 input pin disabled
#pragma config IESO = OFF			// Oscillator Switchover mode disabled

/******************************************************************
** 		      	  GLOBAL VARIABLES (inside the file) 		 	 **
******************************************************************/

extern unsigned char IDCB_serialDispatcher;

/******************************************************************
**              		  MAIN PROGRAM 				  			 **
******************************************************************/

void main (void)
{
 	// Initialisation de l'OS (appel des Callbacks)
	TIOSInitialization();

	// Initialisation des Callbacks
	TIOSSaveCB (&IDCB_serialDispatcher, serialDispatcher, 200);
	
 	// Lancement OS (Boucle infinie)
	TIOSStart();
}

/******************************************************************
** 	        		  	  MAIN FUNCTIONS	    	  			 **
******************************************************************/
