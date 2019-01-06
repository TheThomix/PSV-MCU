#include <stdbool.h>
#include <inttypes.h>
#include <util/delay.h>
#include "userdata.h"

//! initialize the system
void initControl(void);
//! cycle through the handpistols
void measureHandpistols(void);
//! measure voltage and current from the PSU
void measureSupply(void);
//! check if hardware buttons were pressed
void getButtonStates(void);

int main(void)
{
    // system setup
    initControl();

    // should never be leaved!
    while(1)
    {
        // get voltage levels and switch states
        measureHandpistols();
        // change mode when something pressed?
        getButtonStates();
        // update the system variables
        updateCars();

        // get supply current and voltages
        measureSupply();
    }

    // should never be reached
    return 0;
}

void initControl(void)
{
    // we use the "cars" buzzword for any slotcar elements.
    initCars();
    initADC();
}

void measureHandpistols(void)
{
    for (int i = 0; i < 4; i++)
    {
        startADC(i);
    }
}

void measureSupply(void)
{
    startADC(ADC_MUX_PSU_I);
    startADC(ADC_MUX_PSU_U);
}

void getButtonStates(void)
{
    startADC(ADC_MUX_SWITCH_FUEL);
    startADC(ADC_MUX_RAIL_RX);
}