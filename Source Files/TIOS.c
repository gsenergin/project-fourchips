/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "TIOS.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/
void (*CB_PTR_Table[ MAX_CB ])(void);
unsigned int CB_TIME_Table[ MAX_CB ];
volatile unsigned int CB_TICK_Table[ MAX_CB ];

unsigned char IDCB_serialDispatcher = 0;
unsigned char IDCB_stackUpdate = 0;
unsigned char IDCB_getAuthentication = 0;
unsigned char IDCB_waitingOfThePassword = 0;
unsigned char IDCB_Chronometre = 0;
unsigned char IDCB_Clignotement_LED = 0;
unsigned char IDCB_getLight = 0;
unsigned char IDCB_getTemperature = 0;

extern volatile unsigned char RFID_Write_Flag;
extern volatile unsigned char RFID_Read_Flag;
extern volatile unsigned char RFID_i;
extern volatile unsigned char RFID_Read_Resultat[10];

extern volatile unsigned char receivedChar, i_receivedString;
extern char receivedString[21];
extern unsigned char button;

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
	
	// Initialization of the TMR0
	TickInit();
	
	// Initialization of the ETHERNET
	InitAppConfig();
	StackInit();
	
	// Initialization of the TMR1
	initTMR1();

	// Initialization of the USART1
	initUSART1();
	
	// Initialization of the RFID
	initRFID();
	
	// Initialization of the LCD
	initLCD();
	
	// Initialization of the ADC
	initADC();
	setADCChannel(CANALBORNIER);
	ADCAcquisition();
	
	/****     		INITIALIZATION OF INTERRUPTIONS           ****/
	initInterrupts();
 	
 	//Initialisation pour variables CallBack Chrono
 	for (i = 0; i < MAX_CB; i++) {
	 	CB_PTR_Table[i] = 0;
	 	CB_TIME_Table[i] = 0;
  	}
}

void TIOSSaveCB (unsigned char* IDCB, void(*functionPtr)(void), unsigned int CB_time) {
	unsigned char i; 
 	
 	if (*IDCB == 0 | *IDCB == 255) {
	 	// We don't begin at 1 because the IDCB are initialized to 0
	 	for (i = 1; i < MAX_CB && CB_PTR_Table[i] != 0; i++);
	 	
		// If there is an empty place, we save the functionPtr, CB_time and IDCB
	 	if (i < MAX_CB) {
			CB_PTR_Table[i] = functionPtr;
			CB_TIME_Table[i] = CB_time; 
			CB_TICK_Table[i] = 0;	// the CB_TICK is initialized to 0
			
			*IDCB = i;
	  	}
	 	else 
	 		*IDCB = 255;	// If there is no empty place to save the CB, the IDCD is set to 255
	 }		
}

void TIOSRemoveCB (unsigned char* IDCB) {
	if ((*IDCB > 0) && *IDCB < MAX_CB) {
		CB_PTR_Table[*IDCB] = 0;
		CB_TIME_Table[*IDCB] = 0;
		*IDCB = 0;
	}
}

void TIOSStart (void) {
	unsigned char i;
	
	while(1) {
		stackUpdate();
		// A loop on all the CB table
		for (i = 0; i < MAX_CB; i++) {
			if (CB_PTR_Table[i]) {	// If the CB_PTR_Table[i] is different than 0, there is a callback to analyze
				
				//Si on est arrivé au nombre de mS demandé, on appelle la fonction 
				// If the CB_TICK_Table[i] is equal or greater than the CB_TIME_Table[i], we have to call the CB_PTR_Table[i]
				if (CB_TICK_Table[i] >= CB_TIME_Table[i]) { 
					
					CB_TICK_Table[i] = 0;
					CB_PTR_Table[i]();
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
		unsigned char i;
		
	  	for (i = 0; i < MAX_CB; i++) 
	  		CB_TICK_Table[i]++;	// Increment of all the CB_TICK_Table cells
	  	
	  	// Reconfiguration of the TMR1 buffers and interruption flag
	  	TMR1H = 0xFE;
		TMR1L = 0x0B;
	  	TMR1IFLAG = 0;
	}
	
	if (USART1IFLAG) {
		receivedChar = RCREG1;
		
		/* Because the code we receive from the C# program begins and only contains a # character, 
		 * we set the i_receivedString to 0 which determines the place where we have to add the receivedChar
		 * on the receivedString table
		 */
		if (receivedChar == '#')
			i_receivedString = 0;
		
		if (i_receivedString < 21) {	// The frame we receive from the C# program never exceed 21 characters
			receivedString[i_receivedString] = receivedChar;	// We places the receivedChar at the good position on the receivedString table
			i_receivedString++;
			receivedString[i_receivedString] = '\0'; // We add a \0 to the receivedString to be correctly interpreted by the program later
		}
		
		// Reconfiguration of the USART1 interruption flag
		USART1IFLAG = 0;
	}
	
	if (RFIDIFLAG) {
		if (RFID_Read_Flag) { // If it is the response of a read command frame
			RFID_Read_Resultat[RFID_i] = RCREG2;
			RFID_i++;
			
			if (RFID_i >= 10) { // The read command response frame is 10 bytes long
				RFID_i = 0;
				RFID_Read_Flag = OFF;
				PORT_RELAY ^= ON;	// The RELAY switches when a sector is read
			}
		}
		else if (RFID_Write_Flag) {	// If it is the response of a write command frame
			RFID_Read_Resultat[RFID_i] = RCREG2;
			
			RFID_i++;
			
			if (RFID_i >= 6) {	// The write command response frame is 10 bytes long
				RFID_i = 0;
				RFID_Write_Flag = OFF;
			}
		}
		
		// Reconfiguration of the RFID interruption flag
		RFIDIFLAG = 0;
	}
	
	if (INT0IFLAG) {
		Delay10KTCYx(40);
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
			
		// Reconfiguration of the INT0 interruption flag
		INT0IFLAG = 0;
	}
}
	

#pragma interrupt MyInterruptLow
void MyInterruptLow (void)
{
	TickUpdate();	
}
