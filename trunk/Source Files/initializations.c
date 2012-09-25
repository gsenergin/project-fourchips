#include "../Header Files/initializations.h"

/******************************************************************
** 			ENUMERATIONS - DEFINITIONS (inside the file) 		 **
******************************************************************/

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void initBothPriorityInterruptGeneration (void) {
	/****					LOCAL VARIABLES					  ****/

	/****     		 INITIALIZATION OF PERIPHERALS         	  ****/

	/****     		INITIALIZATION OF INTERRUPTIONS           ****/
	INTCONbits.GIE_GIEH = 1;		// Enables all high priority interrupts [p115]
	INTCONbits.PEIE_GIEL = 1;		// Enables all low priority interrupts [p115]
	RCONbits.IPEN = 1;				// Enable priority levels on interrupts [p60]
}	

void initINT0 (void) {
	/****					LOCAL VARIABLES					  ****/

	/****     		 INITIALIZATION OF PERIPHERALS         	  ****/
	TRISBbits.TRISB0 = IN;			// Configure RB0 (INT0) in INPUT (read) [p155]

	/****     		INITIALIZATION OF INTERRUPTIONS           ****/
	INTCONbits.INT0IE = 1;			// Enables the INT0 external interrupt [p115]
	INTCONbits.INT0IF = 0;			// The INT0 external interrupt did not occur [p115]
	INTCON2bits.INTEDG0 = 0;		// Interrupt on falling edge [p116]	
}

void initTMR1 (void) {
	/****					LOCAL VARIABLES					  ****/

	/****     		 INITIALIZATION OF PERIPHERALS         	  ****/
	T1CONbits.TMR1ON = 1;			// Enables Timer1 [p172]
	T1CONbits.TMR1CS = 0b00;		// Timer1 clock source is instruction clock (FOSC/4) [p172]
	T1CONbits.T1CKPS = 0b11;		// Timer1 input clock prescale 1:8 [p172]
	T1GCONbits.TMR1GE = 0;			// Timer1 counts regardless of Timer1 gate function [p173]
	
	/*	TMR1 Incrementation Time = FOSC/4/8 = 2µs
	 *	We want the TMR1 to be on overflow each 1ms, so we need 1ms/2µs (500) incrementations
	 *	We have to configure the pair registers to ((2^16)-1) - 500 = (65536-1) - 500 = 65035 = 0xFE0B
	 */
	TMR1H = 0xFE;
	TMR1L = 0x0B;

	/****     		INITIALIZATION OF INTERRUPTIONS           ****/
	PIR1bits.TMR1IF = 0;		// TMR1 register did not overflow [p118]
	PIE1bits.TMR1IE = 1;		// Enables the TMR1 overflow interrupt [p123]
	IPR1bits.TMR1IP = 1;		// TMR1 overflow interrupt set to high priority [p127]
}	

void initADC (void) {
	/****					LOCAL VARIABLES					  ****/

	/****     		 INITIALIZATION OF PERIPHERALS         	  ****/
	TRISDbits.RD4 = IN;		// Configure RD4 (PHOTODIODE) in INPUT (read) [p155]
	TRISBbits.RB2 = IN;		// Configure RB2 (EXT_INT) in INPUT (read) [p155]

	ANSELDbits.ANSD4 = ANALOGIC;	// Configure RD4 (PHOTODIODE) in ANALOGIQUE [p154]
	ANSELBbits.ANSB2 = ANALOGIC;	// Configure RB2 (EXT_INT) in ANALOGIQUE [p154]

	ADCON0bits.ADON = 1;	// Enables ADC [p300-301]
	ADCON1bits.PVCFG = 0b00;	// A/D VREF+ connected to internal signal, AVDD [p301]
	ADCON1bits.NVCFG = 0b00;	// A/D VREF- connected to internal signal, AVSS [p301]
	ADCON2bits.ADCS = 0b010;	// Conversion Clock (TAD) set to FOSC/32 [p302]
	ADCON2bits.ACQT = 0b101;	// A/D Acquisition time set to 12 TAD [p302]
	ADCON2bits.ADFM = 1;		// A/D Conversion Result Format set to Right justified [p302]

	/****     		INITIALIZATION OF INTERRUPTIONS           ****/
}

void initEUSART (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
}

void initLCD (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     		 INITIALIZATION OF PERIPHERALS         	  ****/
	ANSELAbits.ANSA1 = NUMERIC;	// Configure RA1 (LCD_R/W) in NUMERIC [p153]
	ANSELAbits.ANSA2 = NUMERIC; // Configure RA2 (LCD_E) in NUMERIC [p153]
	ANSELDbits.ANSD5 = NUMERIC; // Configure RD5 (LCD_RS) in NUMERIC [p154]
	ANSELDbits.ANSD0 = NUMERIC; // Configure RD0 (LCD0) in NUMERIC [p154]
	ANSELDbits.ANSD1 = NUMERIC; // Configure RD1 (LCD1) in NUMERIC [p154]
	ANSELDbits.ANSD2 = NUMERIC; // Configure RD2 (LCD2) in NUMERIC [p154]
	ANSELDbits.ANSD3 = NUMERIC; // Configure RD3 (LCD3) in NUMERIC [p154]
	
	/****     				    FUNCTION           			  ****/
	OpenXLCD(FOUR_BIT & LINES_5X7);	
}


void DelayFor18TCY (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
	Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); 
	Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); 
	Nop(); Nop(); Nop(); Nop(); Nop(); Nop(); 
}

void DelayPORXLCD (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
	Delay1KTCYx(60);
}

void DelayXLCD (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
	Delay1KTCYx(20);
}	
