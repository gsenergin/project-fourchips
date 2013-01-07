/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "Modules/chronoModule.h"


/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

unsigned int elapsedMinutes =0;
extern unsigned char IDCB_Chronometre;

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void chronometre (void) {
	/****					LOCAL VARIABLES					  ****/
	unsigned int hours=0, minutes=0;
	char hour[3], minute[3], code[11]="#07@", middle[]=";", ajout[2]="0";
	
	/****     				    FUNCTION           			  ****/
	
	/*We are going to convert the elapsed minutes in hours and minutes*/
	
	elapsedMinutes++; //Every minutes we are connected, we increment it
	hours=elapsedMinutes/60; //We put in an integer variable the number of hours we have been connected
	minutes=elapsedMinutes%60; //We put in an integer variable the number of minutes by the hours we have been connected
	itoa (hours,hour); //We convert the hours in a char
	itoa (minutes,minute); // We convert the minutes in a char
	
	
	// Because we want to send a frame on this format : #07@hh;mm
	// It is necessary to add a 0 when the hours or the minutes are minus than 10
	if(hours<10)
		strcat(code, ajout);	//We concatenate the number "0"
	strcat(code, hour);	//We concatenate the number of hours with the "h"
	strcat(code, middle);	//We concatenate the symbol ";"
	
	if(minutes<10)
		strcat(code, ajout);	//We concatenate the number "0"
	strcat(code, minute);	// We contatenate the number of minutes with the rest
	
	code[ strlen(code) ] = '\n';	// Adds a \n to the end of the frame to be correctly interpreted by the C# program
	
	writeOnUSART1V (code); // We send it to the application with USART  				   
}
