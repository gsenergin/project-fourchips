/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "Modules/brightnessModule.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

extern unsigned char IDCB_getLight;

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void getLight (void)
{
	/****					LOCAL VARIABLES					  ****/
	char currentLightString[7], tableDataToSend[11] = "#05@";
	float currentLight, tempLight;
	
	/****     				    FUNCTION           			  ****/
	tempLight = ADCAcquisition();
	currentLight = tempLight*(100/5);
	ftoa(currentLight, currentLightString, 1, 'F');
	
	strcat(tableDataToSend, currentLightString);
	tableDataToSend[ strlen(tableDataToSend) ] = '\n';	// Adds a \n to the end of the frame to be correctly interpreted by the C# program
	writeOnUSART1V(tableDataToSend);
}	