#ifndef __ADC_H
#define __ADC_H

/******************************************************************
**                                                INCLUDES FILES                                                 **
******************************************************************/

#include "main.h"

/******************************************************************
**                                 ENUMERATIONS - DEFINITIONS                                    **
******************************************************************/

#define CANALPHOTODIODE         24              // Used as channel for ADC acquisition [p293]
#define CANALBORNIER            8               // Used as channel for ADC acquisition [p293]
#define ADCGoDone                       ADCON0bits.GO_NOT_DONE

/******************************************************************
**                                FUNCTION PROTOTYPES                                    **
******************************************************************/

/**
 * Initializes the ADC and configures the photodiode and ext_int
 * port with these options : TRIS = IN, ANSEL = ANALOGIC
 */
void initADC (void);

/**
 * Sets the channel to use for the ADC acquisition
 *
 * @param       canal                   channel <= 27
 */
void setADCChannel (char canal);

/**
 * Makes an average of 10 ADC acquisitions 
 * and returns it as a float number
 *
 * @return                                      average of 10 ADC acquisitions
 */
float ADCAcquisition (void);

#endif