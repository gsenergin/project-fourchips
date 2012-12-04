/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "ADC.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

void initADC (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     		 INITIALIZATION OF PERIPHERALS         	  ****/
	TRISDbits.RD4 = IN;		// Configures RD4 (PHOTODIODE) in INPUT (read) [p155]
	TRISBbits.RB2 = IN;		// Configures RB2 (EXT_INT) in INPUT (read) [p155]

	ANSELDbits.ANSD4 = ANALOGIC;	// Configures RD4 (PHOTODIODE) in ANALOGIQUE [p154]
	ANSELBbits.ANSB2 = ANALOGIC;	// Configures RB2 (EXT_INT) in ANALOGIQUE [p154]

	ADCON0bits.ADON = 1;		// Enables ADC [p300-301]
	ADCON1bits.PVCFG = 0b00;	// A/D VREF+ connected to internal signal, AVDD [p301]
	ADCON1bits.NVCFG = 0b00;	// A/D VREF- connected to internal signal, AVSS [p301]
	ADCON2bits.ADCS = 0b010;	// Conversion Clock (TAD) set to FOSC/32 [p302]
	ADCON2bits.ACQT = 0b101;	// A/D Acquisition time set to 12 TAD [p302]
	ADCON2bits.ADFM = 1;		// A/D Conversion Result Format set to Right justified [p302]
}

void setADCChannel (int canal) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
	if (canal <= 27)
		ADCON0bits.CHS = canal;	
}

float ADCAcquisition (void) {
	/****					LOCAL VARIABLES					  ****/
	int i, result, registreHigh, registreLow;
	float average, resolution = 0.0049;
	
	/****     				    FUNCTION           			  ****/	
	for (i = 0, average = 0; i < 10; i++) {			// Boucle used to make 10 ADC acquisition and add it to average
		ADCGoDone = 1;								// Begins the ADC acquisition
		while (ADCGoDone != 0);						// Waits the end of the ADC acquisition

		registreHigh = ADRESH;						// Copy of ADRESH [p303]
		registreHigh = registreHigh << 8;			// Shifts the ADRESH copy 8 bits to the left
		registreLow = ADRESL;						// Copy of ADRESL [p303]
		result = (registreHigh | registreLow);		// Concatenation of both registers
		
		average += ((float)result * resolution);	// Adds the result to the average
	}
	
	return (average / 10);	// Return the average
}	