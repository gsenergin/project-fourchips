/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "Modules/moduleLight.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

unsigned char IDCB_getLight = 0;
extern char LIGHT[];

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void getLight (void)
{
	char currentLightString[6], tableDataToSend[15];
	float currentLight, tempLight = ADCAcquisition();
	
	if(tempLight <= MAX_LIGHT){
		currentLight = tempLight*(0.03);
		ftoa(currentLight, currentLightString, 5, 'F');
				
		strcpy(tableDataToSend, LIGHT);
		strcat(tableDataToSend, currentLightString);
		tableDataToSend[ strlen(tableDataToSend) ] = '\n';	// Adds a \n to the end of the frame to be correctly interpreted by the C# program
		writeOnUSART1V(tableDataToSend);
	}
}	