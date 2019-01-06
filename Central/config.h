#ifndef CONFIG_H
#define CONFIG_H

//! needed for the port, pin and PXY defines
#include <avr/io.h>

//! read bit ( we assume that any pins are active low)
#define _RB(port,bit) (!(port & (1 << bit)))
//! write bit
#define _WB(port,bit) (port |= (1 << bit))
//! clear bit
#define _CB(port,bit) (port &= ~(1 << bit))

//! mux value for hand pistol potentiometer 
#define ADC_MUX_POT_0 0
//! mux value for hand pistol potentiometer 
#define ADC_MUX_POT_1 1
//! mux value for hand pistol potentiometer 
#define ADC_MUX_POT_2 2
//! mux value for hand pistol potentiometer 
#define ADC_MUX_POT_3 3
//! mux value for psu voltage divider
#define ADC_MUX_PSU_U 4
//! mux value for psu current sense
#define ADC_MUX_PSU_I 5
//! fuel switch will be encoded by voltage levels
#define ADC_MUX_SWITCH_FUEL 6
//! sense value of the rail
#define ADC_MUX_RAIL_RX 7

#define PORT_PISTOLSW PORTB
#define PIN_PISTOLSW PINB
#define PISTOL_0 PB0
#define PISTOL_1 PB1
#define PISTOL_2 PB2
#define PISTOL_3 PB3

#define PORT_PISTOLSW_ALL PORTD
// or connected sense pin, most one of the external int interrupts
#define PISTOL_ALL PD2

//! port for the modulating rail data
#define PORT_RAILTX PORTD
//! pin of the modulated rail data
#define RAIL_TX PD4

//! input port of hardware user interface
#define PORT_BUTTONS PORTC 
//! pin values of hardware user interface
#define PIN_BUTTONS PINC
//! escape button
#define BTN_ESC PC2
//! start button
#define BTN_START PC3
//! fuel button
#define BTN_FUEL PC4
//! speed button
#define BTN_SPEED PC5
//! brake button
#define BTN_BRAKE PC6
//! code button
#define BTN_CODE PC7

//! the start flag port
#define FLAG_PORT PORTB
//! pin of the start flag
#define START_FLAG PB4

//! user interface led output port
#define PORT_LED PORTD
#define LED_0 PD0
#define LED_1 PD1
#define LED_2 PD3
#define LED_3 PD5
#define LED_4 PD6

#endif