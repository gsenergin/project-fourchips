/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "Modules/moduleTemp.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

unsigned char IDCB_getTemperature = 0;
extern char TEMP[];

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void getTemperature(void)
{
	char currentTempString[6], tableDataToSend[15];
	
	float currentTemp = Read_Temperature();
	
	if(currentTemp < 50){
	
		ftoa(currentTemp, currentTempString, 1, 'F');
		
		strcpy(tableDataToSend, TEMP);
		strcat(tableDataToSend, currentTempString);
		tableDataToSend[ strlen(tableDataToSend) ] = '\n';	// Adds a \n to the end of the frame to be correctly interpreted by the C# program
		writeOnUSART1V(tableDataToSend);
	}

	Convert_Temperature();
}