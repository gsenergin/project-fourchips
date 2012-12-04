#ifndef __MYETHERNET_H
#define __MYETHERNET_H

#include "ETHERNET/Compiler.h"
#include "ETHERNET/HardwareProfile.h"
#include "ETHERNET/TCPIPConfig.h"
#include "ETHERNET/TCPIP.h"
#include "ETHERNET/StackTsk.h"
#include "ETHERNET/AppConfig.h"

#define MY_HOST_NAME			"My Board"

#define MY_MAC_BYTE1            (0x00)	// Use the default of 00-04-A3-00-00-01
#define MY_MAC_BYTE2            (0x04)	// if using an ENCX24J600, MRF24WB0M, or
#define MY_MAC_BYTE3            (0xA3)	// PIC32MX6XX/7XX internal Ethernet 
#define MY_MAC_BYTE4            (0x00)	// controller and wish to use the 
#define MY_MAC_BYTE5            (0x00)	// internal factory programmed MAC
#define MY_MAC_BYTE6            (0x01)	// address instead.

#define MY_IP_ADDR_BYTE1        (192ul)	//adresse ip : 192.168.1.254
#define MY_IP_ADDR_BYTE2        (168ul)
#define MY_IP_ADDR_BYTE3        (1ul)
#define MY_IP_ADDR_BYTE4        (254ul)

#define MY_MASK_BYTE1           (255ul)	//masque 255.255.255.0
#define MY_MASK_BYTE2           (255ul)
#define MY_MASK_BYTE3           (255ul)
#define MY_MASK_BYTE4           (0ul)

#define MY_GATEWAY_BYTE1           (192ul)
#define MY_GATEWAY_BYTE2           (168ul)
#define MY_GATEWAY_BYTE3           (1ul)
#define MY_GATEWAY_BYTE4           (1ul)

#define MY_PRIMARY_DNS_BYTE1	(10ul)
#define MY_PRIMARY_DNS_BYTE2	(1ul)
#define MY_PRIMARY_DNS_BYTE3	(11ul)
#define MY_PRIMARY_DNS_BYTE4	(254ul)

#define MY_SECONDARY_DNS_BYTE1	(0ul)
#define MY_SECONDARY_DNS_BYTE2	(0ul)
#define MY_SECONDARY_DNS_BYTE3	(0ul)
#define MY_SECONDARY_DNS_BYTE4	(0ul)

#endif
