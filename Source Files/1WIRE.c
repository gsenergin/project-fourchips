/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "1WIRE.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/


int OWInit (void) {
	/****					LOCAL VARIABLES					  ****/
	int state;
	
	/****     				    FUNCTION           			  ****/	
	DQ_LOW;
	
	Delay10TCYx(200);	//500탎
	
	DQ_RELEASE;
	
	Delay10TCYx(40);	//100탎
	
	state = DQ_READ;
	
	Delay10TCYx(160);	//400탎
	
	return state;
}

void OWWriteBit (int bit) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/	
	DQ_LOW;
	
	if (bit)
		Delay10TCYx(4);		//10탎
	else
		Delay10TCYx(40);	//100탎
		
	DQ_RELEASE;
	
	if (bit)
		Delay10TCYx(24);		//60탎
		
	Delay10TCYx(4);		//10탎 (recovery) (time obliged between 2 writes)
}

int OWReadBit (void) {
	/****					LOCAL VARIABLES					  ****/
	int bit;
	
	/****     				    FUNCTION           			  ****/	
	DQ_LOW;
	
	Nop();Nop();Nop();Nop();		//2탎
	Nop();Nop();Nop();Nop();
	
	DQ_RELEASE;
	
	Delay10TCYx(4);		//10탎
	
	bit = (int)DQ_READ;
	
	Delay10TCYx(24);		//60탎
	
	Delay10TCYx(4);		//10탎 (recovery) (time obliged between 2 reads)
	
	return bit;
}

void OWWriteByte (int byte) {
	/****					LOCAL VARIABLES					  ****/
	int i;
	
	/****     				    FUNCTION           			  ****/	
	// Loop to write each bit in the byte, LS-bit first
	for (i = 0; i < 8; i++)	{
		OWWriteBit(byte & 0x01);
		
		// shift the data byte for the next bit
		byte >>= 1;
	}
}	

int OWReadByte (void) {
	/****					LOCAL VARIABLES					  ****/
	int i, byte = 0;
	
	/****     				    FUNCTION           			  ****/	
	for (i = 0; i < 8; i++)
	{
		// shift the result to get it ready for the next bit
		byte >>= 1;
		
		// if result is one, then set MS bit
		if (OWReadBit())
			byte |= 0x80;
	}
	return byte;
}

void Convert_Temperature (void) {
	/****					LOCAL VARIABLES					  ****/
	
	/****     				    FUNCTION           			  ****/
	OWInit();								// master resets bus
	OWWriteByte(0xCC);						// skip ROM
	OWWriteByte(0x44);						// convert temperature
	
	// Delay of 800탎
	//Delay10KTCYx(200);
	//Delay10KTCYx(120);
}

float Read_Temperature (void) {
	/****					LOCAL VARIABLES					  ****/
	unsigned char scratchpad[10];
	int i, msb, lsb, result;
	float temperature;
	
	/****     				    FUNCTION           			  ****/	
	OWInit();								// master resets bus
	OWWriteByte(0xCC);						// skip ROM
	OWWriteByte(0xBE);						// read scratch pad

	for (i = 0; i < 9; i++)						// read 9 bytes from scratchpad
		scratchpad[i] = OWReadByte();

	msb = scratchpad[1] & 0x7;					// load 3 bits of the MSB, masking any sign bits
	msb = msb << 8;						// shift the MSB left 8 bits
	lsb = scratchpad[0];
	result = (msb | lsb);					// load all 8 bits of the LSB

	if (msb & 0x80)						// sign bit set, temp is negative
		result *= -1;

	temperature = (float)result * 0.0625;
    
    return temperature;
}