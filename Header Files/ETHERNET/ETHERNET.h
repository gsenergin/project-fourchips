#ifndef __ETHERNET_H
#define __ETHERNET_H

/******************************************************************
**						  INCLUDES FILES						 **
******************************************************************/

#include "main.h"
#include "ETHERNET/Compiler.h"
#include "ETHERNET/HardwareProfile.h"
#include "ETHERNET/TCPIPConfig.h"
#include "ETHERNET/TCPIP.h"
#include "ETHERNET/StackTsk.h"
#include "ETHERNET/AppConfig.h"

/******************************************************************
** 				   ENUMERATIONS - DEFINITIONS					 **
******************************************************************/

/******************************************************************
** 	        		  FUNCTION PROTOTYPES	    	  			 **
******************************************************************/

unsigned long getIP_ADDR_BYTE1 (void);
unsigned long getIP_ADDR_BYTE2 (void);
unsigned long getIP_ADDR_BYTE3 (void);
unsigned long getIP_ADDR_BYTE4 (void);

unsigned long getMASK_BYTE1 (void);
unsigned long getMASK_BYTE2 (void);
unsigned long getMASK_BYTE3 (void);
unsigned long getMASK_BYTE4 (void);

unsigned long getGATEWAY_BYTE1 (void);
unsigned long getGATEWAY_BYTE2 (void);
unsigned long getGATEWAY_BYTE3 (void);
unsigned long getGATEWAY_BYTE4 (void);

unsigned long getPRIMARY_DNS_BYTE1 (void);
unsigned long getPRIMARY_DNS_BYTE2 (void);
unsigned long getPRIMARY_DNS_BYTE3 (void);
unsigned long getPRIMARY_DNS_BYTE4 (void);

unsigned long getSECONDARY_DNS_BYTE1 (void);
unsigned long getSECONDARY_DNS_BYTE2 (void);
unsigned long getSECONDARY_DNS_BYTE3 (void);
unsigned long getSECONDARY_DNS_BYTE4 (void);

void setIP_ADDR (unsigned long newIP_ADDR_BYTE1, unsigned long newIP_ADDR_BYTE2, unsigned long newIP_ADDR_BYTE3, unsigned long newIP_ADDR_BYTE4);

void setMASK (unsigned long newMASK_BYTE1, unsigned long newMASK_BYTE2, unsigned long newMASK_BYTE3, unsigned long newMASK_BYTE4);

void setGATEWAY (unsigned long newGATEWAY_BYTE1, unsigned long newGATEWAY_BYTE2, unsigned long newGATEWAY_BYTE3, unsigned long newGATEWAY_BYTE4);

void setPRIMARY_DNS (unsigned long newPRIMARY_DNS_BYTE1, unsigned long newPRIMARY_DNS_BYTE2, unsigned long newPRIMARY_DNS_BYTE3, unsigned long newPRIMARY_DNS_BYTE4);

void setSECONDARY_DNS (unsigned long newSECONDARY_DNS_BYTE1, unsigned long newSECONDARY_DNS_BYTE2, unsigned long newSECONDARY_DNS_BYTE3, unsigned long newSECONDARY_DNS_BYTE4);

#endif
