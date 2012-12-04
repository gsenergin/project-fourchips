#ifndef __TIOS_H
#define __TIOS_H

/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "main.h"

/******************************************************************
** 				   ENUMERATIONS - DEFINITIONS					 **
******************************************************************/

//D�finit le nombre maximal de callback de type Chrono
#define	MAXCALLBACKCHRONO		10

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

//Initialisation de TIOS
void TIOSInitialization (void);

//Enregistrer des fonctions callback li�es au temps
//Retourne un ID associ� � l'enregistrement
void TIOSSaveCallBack (unsigned char* IDCB, void(*ptFonction)(void), unsigned int tps); 

//Retirer des fonctions callback li�es au temps, prend l'ID du CallBack comme argument
void TIOSRetirerCB_TIMER (unsigned char* IDCB);

//D�marrage de la boucle principale
void TIOSStart (void);

/******************************************************************
** 	    	   	DECLARATION OF INTERRUPT ROUTINES 	    		 **
******************************************************************/

void MyInterruptHigh (void);

void MyInterruptLow (void);

#endif
