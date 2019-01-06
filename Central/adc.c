#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>

#include "adc.h"
#include "userdata.h"
#include "systemdata.h"

uint8_t currentChannel = 0;
_Bool adcActive = false;

void initADC(void)
{
    // interrupt enable
    ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) | (1 << ADIE);
    // free running mode
    SFIOR = 0x00;

    currentChannel = 0;
    adcActive = false;

    // we need a first initialization of the system
    startADC(0);
}

void startADC(uint8_t channel)
{
    while(allowADC()) _delay_ms(1);

    // 5v is reference value, left adjust the result
    ADMUX = (1 << ADLAR) | (1<<REFS0) | channel;
    // start the conversion
    ADCSRA |= (1 << ADSC);

    currentChannel = channel;
    adcActive = true;
}

_Bool allowADC(void)
{
    return !adcActive;
}

ISR(ADC_vect)
{
    if ( currentChannel < 4 ) 
    {
        carSetSpeed(currentChannel, ADCH);
    }
    else
    {
        switch ( currentChannel ) 
        {
            case ADC_MUX_PSU_U :
                break;

            case ADC_MUX_PSU_I :
                break;

            case ADC_MUX_SWITCH_FUEL :
                break;

            case ADC_MUX_RAIL_RX :
                break;

            default:
                break;
        }
    }

    adcActive = false;
}