/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "TIOS.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/
void (*MaCB[MAXCALLBACKCHRONO])(void);
unsigned int TempsCB[MAXCALLBACKCHRONO];
volatile unsigned int TickCB[MAXCALLBACKCHRONO];

extern volatile unsigned char RFID_Write_Flag;
extern volatile unsigned char RFID_Read_Flag;
extern volatile unsigned char RFID_i;
extern volatile unsigned char RFID_Read_Resultat[10];

extern volatile unsigned char receivedChar, i_receivedString;
extern char receivedString[21], button;

/******************************************************************
** 	       COMPILATION INSTRUCTIONS FOR INTERRUPTIONS 	    	 **
******************************************************************/

#pragma code highVector=0x0008
void atInterrupthigh(void){
	_asm GOTO MyInterruptHigh _endasm
}
#pragma code

#pragma code lowVector=0x0018
void atInterruptlow(void){
	_asm GOTO MyInterruptLow _endasm
}
#pragma code

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void TIOSInitialization (void) {
	/****					LOCAL VARIABLES					  ****/
 	unsigned char i;
 	
	/****     		 INITIALIZATION OF PERIPHERALS         	  ****/

	// Defines the FOSC to 16MHz [p32]
	OSCCONbits.IRCF0 = 0b111;
	
	// Defines all ANSELx registers in NUMERIC [p153-155]
	ANSELA = NUMERIC;
	ANSELB = NUMERIC;
	ANSELC = NUMERIC;
	ANSELD = NUMERIC;
	ANSELE = NUMERIC;
	
	// Initialization of the LED
	TRIS_LED = OUT;		// Configures the LED in OUTPUT (write)
	PORT_LED = OFF;		// Turns off the LED
	
	// Initialization of the RELAY
	TRIS_RELAY = OUT;	// Configures the RELAY in OUTPUT (write)
	PORT_RELAY = OFF;	// Turns off the RELAY
	
	// Initialization of INTO
	TRIS_INT0 = IN;		// Configures INT0 in INPUT (read)
	TRIS_UP = IN;		// Configures the UP button in INPUT (read)
	TRIS_DOWN = IN;		// Configures the DOWN button in INPUT (read)
	TRIS_RIGHT = IN;	// Configures the RIGHT button in INPUT (read)
	TRIS_LEFT = IN;		// Configures the LEFT button in INPUT (read)
	TRIS_CENTER = IN;	// Configures the CENTER button in INPUT (read)
	
	// Initialization of the TMR1
	initTMR1();

	// Initialization of the USART1
	initUSART1();
	
	// Initialization of the RFID
	initRFID();
	
	// Initialization of the LCD
	initLCD();
	
	/****     		INITIALIZATION OF INTERRUPTIONS           ****/
	initInterrupts();
 	
 	//Initialisation pour variables CallBack Chrono
 	for (i = 0; i < MAXCALLBACKCHRONO; i++)
 	{
  		 MaCB[i] = 0;
  		 TempsCB[i] = 0;
  	}
} 

// ****************  EnregistrerFonctionDeRappel ******************************
// Sauve l'adresse de la fonction à rappeler. Lorsque le nombre d'interruptions
// aura atteint temps millisecondes, le système rappellera la fonction
// *************************************************************************
void TIOSSaveCallBack (unsigned char* IDCB, void(*ptFonction)(void), unsigned int tps) {
 	unsigned char i; 
 	
 	if (*IDCB == 0 | *IDCB == 255) {
	 	// on commence à 1 car les IDCB sont initialisés à 0 !!
	 	for (i = 1; MaCB[i] != 0 && i < MAXCALLBACKCHRONO; i++);
	 	
		//S'il reste de la place on enregistre et on retourne 0 (opération réussie)
	 	if (i < MAXCALLBACKCHRONO) {
			MaCB[i] = ptFonction;
			TempsCB[i] = tps; 
			TickCB[i] = 0; //Initialiser le compteur à 0;
			
			*IDCB = i; // ID du call back
	  	}
	 	else 
	 		*IDCB = 255; //Il n'y a plus de place pour enregistrer un callback
	 }		
}


// ****************  Retirer fonction de rappel ******************************
// Libère l'emplacement de la callback
// *************************************************************************
void TIOSRetirerCB_TIMER (unsigned char* IDCB) {
	if ((*IDCB > 0) && *IDCB < MAXCALLBACKCHRONO) {
		MaCB[*IDCB] = 0;
		TempsCB[*IDCB] = 0;
		*IDCB = 0;
	}
}



// ****************  Boucle principale de l'OS ******************************
// Boucle infinie qui attend des événement liés aux interruptions pour 
// appeler les fonctions enregistrées
// *************************************************************************
void TIOSStart (void) {
	unsigned char idx;
	
	while(1) {
		// Check les conditions pour rappeler les fonctions liées au temps 
		for (idx = 0; idx < MAXCALLBACKCHRONO; idx++)
		{
			if (MaCB[idx]) {//Si on a l'adresse d'une fonction CB à cet index
				//Si on est arrivé au nombre de mS demandé, on appelle la fonction 
				if (TickCB[idx] >= TempsCB[idx]) { 
					TickCB[idx] = 0;
					MaCB[idx]();  //Rappel de la fonction enregistrée!
				}
			}	
		}
	}
}


/******************************************************************
**                 CONTENT INTERRUPT ROUTINES 				  	 **
******************************************************************/
           
#pragma interrupt MyInterruptHigh
void MyInterruptHigh (void)
{
	if (TMR1IFLAG) {
		// Ajourner tous les ticks
		unsigned char i;
	  	for (i = 0; i < MAXCALLBACKCHRONO; i++) TickCB[i]++;
	  	
	  	// reconfiguration du Timer0
	  	TMR1H = 0xFE;
		TMR1L = 0x0B;
	  	TMR1IFLAG = 0;
	}
	
	if (RFIDIFLAG) {
		if (RFID_Read_Flag) {
			RFID_Read_Resultat[RFID_i] = RCREG2;
			RFID_i++;
			
			if (RFID_i >= 10) {
				RFID_i = 0;
				RFID_Read_Flag = OFF;
				PORT_RELAY ^= ON;
			}
		}
		else if (RFID_Write_Flag) {
			RFID_Read_Resultat[RFID_i] = RCREG2;
			
			RFID_i++;
			
			if (RFID_i >= 6) {
				RFID_i = 0;
				RFID_Write_Flag = OFF;
			}
		}
		
		RFIDIFLAG = 0;
	}
	
	if (INT0IFLAG) {
		if (PORT_UP == 0)
			button = UP;
		else if (PORT_DOWN == 0)
			button = DOWN;
		else if (PORT_LEFT == 0)
			button = LEFT;
		else if (PORT_CENTER == 0)
			button = CENTER;
		else if (PORT_RIGHT == 0)
			button = RIGHT;
			
		INT0IFLAG = 0;
	}	
}
	

#pragma interrupt MyInterruptLow
void MyInterruptLow (void)
{
	if (USART1IFLAG) {
		receivedChar = RCREG1;
		
		if (receivedChar == '#')
			i_receivedString = 0;
		
		if (i_receivedString < 21) {
			receivedString[i_receivedString] = receivedChar;
			i_receivedString++;
			receivedString[i_receivedString] = '\0';
		}
		
		USART1IFLAG = 0;
	}	
}
