#ifndef ADC_H
#define ADC_H

#include "config.h"

//! complete init for adc
void initADC(void);
//! on which channel should we do the mux
void startADC(uint8_t channel);
//! check if we are allowed to start the ADC
_Bool allowADC(void);

#endif