/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "ETHERNET/ETHERNET.h"

/******************************************************************
** 		      	   GLOBAL VARIABLES (inside the file)			 **
******************************************************************/

APP_CONFIG AppConfig;
unsigned long IP_ADDR_BYTE1 = 192, IP_ADDR_BYTE2 = 168, IP_ADDR_BYTE3 = 1, IP_ADDR_BYTE4 = 200;
unsigned long MASK_BYTE1 = 255, MASK_BYTE2 = 255, MASK_BYTE3 = 255, MASK_BYTE4 = 0;
unsigned long GATEWAY_BYTE1 = 192, GATEWAY_BYTE2 = 162, GATEWAY_BYTE3 = 1, GATEWAY_BYTE4 = 254;
unsigned long PRIMARY_DNS_BYTE1 = 8, PRIMARY_DNS_BYTE2 = 8, PRIMARY_DNS_BYTE3 = 8, PRIMARY_DNS_BYTE4 = 8;
unsigned long SECONDARY_DNS_BYTE1 = 8, SECONDARY_DNS_BYTE2 = 8, SECONDARY_DNS_BYTE3 = 4, SECONDARY_DNS_BYTE4 = 4;

/******************************************************************
** 		      	   		   MAIN FUNCTIONS 				  		 **
******************************************************************/

unsigned long getIP_ADDR_BYTE1 (void) { return IP_ADDR_BYTE1; }
unsigned long getIP_ADDR_BYTE2 (void) { return IP_ADDR_BYTE2; }
unsigned long getIP_ADDR_BYTE3 (void) { return IP_ADDR_BYTE3; }
unsigned long getIP_ADDR_BYTE4 (void) { return IP_ADDR_BYTE4; }

unsigned long getMASK_BYTE1 (void) { return MASK_BYTE1; }
unsigned long getMASK_BYTE2 (void) { return MASK_BYTE2; }
unsigned long getMASK_BYTE3 (void) { return MASK_BYTE3; }
unsigned long getMASK_BYTE4 (void) { return MASK_BYTE4; }

unsigned long getGATEWAY_BYTE1 (void) { return GATEWAY_BYTE1; }
unsigned long getGATEWAY_BYTE2 (void) { return GATEWAY_BYTE2; }
unsigned long getGATEWAY_BYTE3 (void) { return GATEWAY_BYTE3; }
unsigned long getGATEWAY_BYTE4 (void) { return GATEWAY_BYTE4; }

unsigned long getPRIMARY_DNS_BYTE1 (void) { return PRIMARY_DNS_BYTE1; }
unsigned long getPRIMARY_DNS_BYTE2 (void) { return PRIMARY_DNS_BYTE2; }
unsigned long getPRIMARY_DNS_BYTE3 (void) { return PRIMARY_DNS_BYTE3; }
unsigned long getPRIMARY_DNS_BYTE4 (void) { return PRIMARY_DNS_BYTE4; }

unsigned long getSECONDARY_DNS_BYTE1 (void) { return SECONDARY_DNS_BYTE1; }
unsigned long getSECONDARY_DNS_BYTE2 (void) { return SECONDARY_DNS_BYTE2; }
unsigned long getSECONDARY_DNS_BYTE3 (void) { return SECONDARY_DNS_BYTE3; }
unsigned long getSECONDARY_DNS_BYTE4 (void) { return SECONDARY_DNS_BYTE4; }

void setIP_ADDR (unsigned long newIP_ADDR_BYTE1, unsigned long newIP_ADDR_BYTE2, unsigned long newIP_ADDR_BYTE3, unsigned long newIP_ADDR_BYTE4) {
	IP_ADDR_BYTE1 = newIP_ADDR_BYTE1;
	IP_ADDR_BYTE2 = newIP_ADDR_BYTE2;
	IP_ADDR_BYTE3 = newIP_ADDR_BYTE3;
	IP_ADDR_BYTE4 = newIP_ADDR_BYTE4;
	InitAppConfig();
}

void setMASK (unsigned long newMASK_BYTE1, unsigned long newMASK_BYTE2, unsigned long newMASK_BYTE3, unsigned long newMASK_BYTE4) {
	MASK_BYTE1 = newMASK_BYTE1;
	MASK_BYTE2 = newMASK_BYTE2;
	MASK_BYTE3 = newMASK_BYTE3;
	MASK_BYTE4 = newMASK_BYTE4;
	InitAppConfig();
}

void setGATEWAY (unsigned long newGATEWAY_BYTE1, unsigned long newGATEWAY_BYTE2, unsigned long newGATEWAY_BYTE3, unsigned long newGATEWAY_BYTE4) {
	GATEWAY_BYTE1 = newGATEWAY_BYTE1;
	GATEWAY_BYTE2 = newGATEWAY_BYTE2;
	GATEWAY_BYTE3 = newGATEWAY_BYTE3;
	GATEWAY_BYTE4 = newGATEWAY_BYTE4;
	InitAppConfig();
}

void setPRIMARY_DNS (unsigned long newPRIMARY_DNS_BYTE1, unsigned long newPRIMARY_DNS_BYTE2, unsigned long newPRIMARY_DNS_BYTE3, unsigned long newPRIMARY_DNS_BYTE4) {
	PRIMARY_DNS_BYTE1 = newPRIMARY_DNS_BYTE1;
	PRIMARY_DNS_BYTE2 = newPRIMARY_DNS_BYTE2;
	PRIMARY_DNS_BYTE3 = newPRIMARY_DNS_BYTE3;
	PRIMARY_DNS_BYTE4 = newPRIMARY_DNS_BYTE4;
	InitAppConfig();
}

void setSECONDARY_DNS (unsigned long newSECONDARY_DNS_BYTE1, unsigned long newSECONDARY_DNS_BYTE2, unsigned long newSECONDARY_DNS_BYTE3, unsigned long newSECONDARY_DNS_BYTE4) {
	SECONDARY_DNS_BYTE1 = newSECONDARY_DNS_BYTE1;
	SECONDARY_DNS_BYTE2 = newSECONDARY_DNS_BYTE2;
	SECONDARY_DNS_BYTE3 = newSECONDARY_DNS_BYTE3;
	SECONDARY_DNS_BYTE4 = newSECONDARY_DNS_BYTE4;
	InitAppConfig();
}