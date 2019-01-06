#ifndef USERDATA_H
#define USERDATA_H

#include <stdbool.h>
#include <inttypes.h>

#define MAX_CARS 8

typedef struct handpistol
{
    // this will be modulated to the tracks
    //! current output speed
    uint8_t speed;
    //! switch the lanes
    _Bool switchLanes;

    // raw measured data
    //! measured hand pistol value
    uint8_t pot_value;
    //! detected switch pressed
    _Bool swPressed;
    
    // configuration of the handpistol. most of these
    // will be a low pass filter
    //! allow the switch
    _Bool swAllow;
    //! maximum allowed speed
    uint8_t maxSpeed;
    //! acceleration of a user
    uint8_t acceleration;
    //! available fuel
    uint16_t fuel;
    //! fuel usage
    uint8_t fuelConsumption;
    //! refuel rate
    uint16_t refuelRate;
    //! maximum fuel
    uint16_t maxFuel;
} handpistol, *hpistol;

// //! instances of the cars
// extern handpistol car[MAX_CARS];

//! outside call function to call
void initCars(void);
//! outside call to update all data
void updateCars(void);
//! pitlane call function
void carRefuel(uint8_t id);
//! get car speed
uint8_t carSpeed(uint8_t id);
//! get the switching lanes state
_Bool carSwitchLanes(uint8_t id);
//! update from adc measurement
void carSetSpeed(uint8_t id, uint8_t adc);
//! update from switch states
void carSetSwitch(uint8_t id, _Bool sw);


#endif