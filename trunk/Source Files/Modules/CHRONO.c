/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "Modules/CHRONO.h"


/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

unsigned int elapsedMinutes =0;
char middle[]=";";
char ajout[2]="0";
unsigned char IDCB_Chronometre = 0;

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void chronometre (void) {
	unsigned int hours=0; 
	unsigned int minutes=0;
	char hour[3];
	char minute[3];
	char code[11]="#07@";
	
	/*We are going to convert the elapsed minutes in hours and minutes*/
	
	elapsedMinutes++; //Every minutes we are connected, we increment it
	hours=elapsedMinutes/60; //We put in an integer variable the number of hours we have been connected
	minutes=elapsedMinutes%60; //We put in an integer variable the number of minutes by the hours we have been connected
	itoa (hours,hour); //We convert the hours in a char
	itoa (minutes,minute); // We convert the minutes in a char
	
	if(hours<10 && minutes<10)

	{strcat(code, ajout);
	strcat(code, hour);
	strcat(code, middle); //We concatenate the number of hours with the "h"
	strcat(code, ajout);
	strcat(code, minute);// We contatenate the number of minutes with the rest
	code[ strlen(code) ] = '\n';	// Adds a \n to the end of the frame to be correctly interpreted by the C# program
	writeOnUSART1V (code); // We send it to the application with USART
	
	}
	
	else{
		
		if(hours<10)
	
		{strcat(code, ajout);
		strcat(code, hour);
		strcat(code, middle); //We concatenate the number of hours with the "h"
		strcat(code, minute);// We contatenate the number of minutes with the rest
		code[ strlen(code) ] = '\n';	// Adds a \n to the end of the frame to be correctly interpreted by the C# program
		writeOnUSART1V (code); // We send it to the application with USART
		
		}
	
	else {
		
		if(minutes<10)
		
		{
	
	strcat(code, hour);
	strcat(code, middle); //We concatenate the number of hours with the "h"
	strcat(code, ajout);
	strcat(code, minute);// We contatenate the number of minutes with the rest
	code[ strlen(code) ] = '\n';	// Adds a \n to the end of the frame to be correctly interpreted by the C# program
	writeOnUSART1V (code); // We send it to the application with USART
		}
		
		else{
		
	strcat(code, hour);
	strcat(code, middle); //We concatenate the number of hours with the "h"
	strcat(code, minute);// We contatenate the number of minutes with the rest
	code[ strlen(code) ] = '\n';	// Adds a \n to the end of the frame to be correctly interpreted by the C# program
	writeOnUSART1V (code); // We send it to the application with USART
		}		
		
	}	
	
	}

  				   
}
