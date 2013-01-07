/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "Modules/temperatureModule.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

extern unsigned char IDCB_getTemperature;
extern char TEMP[];

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void getTemperature(void)
{
	/****					LOCAL VARIABLES					  ****/
	char currentTempString[6], tableDataToSend[10];
			
	/****     				    FUNCTION           			  ****/
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