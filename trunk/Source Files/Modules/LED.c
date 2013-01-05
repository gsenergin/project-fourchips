/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "Modules/LED.h"


/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/
unsigned char IDCB_Clignotement_LED = 0;
char ONLED[]="#06@ON";
extern char LED[];
char aquiredFrequence[3];
unsigned float defaultFrequence=500;	
extern unsigned int CB_TIME_Table[MAX_CB];
unsigned int frequence=0;
unsigned float calcul=0;
/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void clignotementLED(char receivedString[] ){
	char i;
	
	if(strncmp(receivedString, ONLED, 5) == 0){
		if(strncmp(receivedString, ONLED, 6) == 0){
			TIOSSaveCB (&IDCB_Clignotement_LED, clignotement, defaultFrequence);
		}
		else {
			TIOSRemoveCB (&IDCB_Clignotement_LED);
			PORT_LED=OFF;		 
		}
	}	
	else{
		
		for (i = 0; i < 2 && receivedString[i] != '\0'; i++)
			aquiredFrequence[i] = receivedString[i + 4];
			
		aquiredFrequence[i] = '\0';
		
		calcul = 1/atof(aquiredFrequence);
		calcul=(calcul/2)*1000;
		frequence=calcul;

		CB_TIME_Table[IDCB_Clignotement_LED] = frequence;
	}	
}

void clignotement (void){
	PORT_LED ^= ON;
} 	