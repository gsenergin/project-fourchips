/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "Modules/ledModule.h"


/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/
extern unsigned char IDCB_Clignotement_LED;
extern unsigned int CB_TIME_Table[MAX_CB];

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void clignotementLED(char receivedString[] ){
	/****					LOCAL VARIABLES					  ****/
	char i, aquiredFrequence[3];
	unsigned char frequence = 0;
	unsigned float calcul=0;
	
	/****     				    FUNCTION           			  ****/
		
	// We could have 3 types of received frames : #06@ON, #06@OFF, #06@Frequency (Frequency = a number)
	// We first checks if the 5th received character is O or not.
	if(receivedString[4] == 'O'){
		if(receivedString[5] == 'N'){ // If the 6th received character is N
			TIOSSaveCB (&IDCB_Clignotement_LED, clignotement, 500); // 500 is the default frequency sets on the C# program
		}
		else { // else, it is automatically a #06@OFF received frame
			TIOSRemoveCB (&IDCB_Clignotement_LED);
			PORT_LED=OFF;		 
		}
	}	
	else{ // When it is a #06@Frequency received frame
		// Copy the frequency into the aquiredFrequency string
		for (i = 0; i < 2 && receivedString[i] != '\0'; i++)
			aquiredFrequence[i] = receivedString[i + 4];
			
		aquiredFrequence[i] = '\0';
		
		// Manipulation of the string to get the frequency in the correct char format
		calcul = 1/atof(aquiredFrequence);
		calcul=(calcul/2)*1000;
		frequence=calcul;

		CB_TIME_Table[IDCB_Clignotement_LED] = frequence; // Change the call TIME of the CB
	}	
}

void clignotement (void){
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
	PORT_LED ^= ON;
} 	