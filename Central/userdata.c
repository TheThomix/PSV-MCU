#include "userdata.h"

#define INIT_ACCEL 15U
#define INIT_MAXSPEED 15U
#define INIT_FUEL 32768U
#define INIT_FUELCONSUMPTION (128/INIT_MAXSPEED)
#define INIT_REFUEL 1024U
#define INIT_MAXFUEL 32768U

// array of car instances
handpistol car[MAX_CARS];

//! atomic init
void initCar(hpistol usr);
//! update the values and 
void updateData(hpistol usr);
//! special case if in the pitlane. increase the fuel
void refuel(hpistol usr);
//! set raw measurement data
void setRawSpeed(hpistol usr, uint8_t adc);
//! set raw measurement data
void setRawSwitch(hpistol usr, _Bool sw);
//! easy to use in interrupts
uint8_t getSpeed(hpistol usr);
//! easy to use in interrupts
_Bool getSwitchLanes(hpistol usr);


void carRefuel(uint8_t id)
{
    refuel(&car[id]);
}

void updateCars(void)
{
    static uint8_t i;
    for (i = 0; i < MAX_CARS; i++ ) 
    {
        updateData(&car[i]);
    }
}

uint8_t carSpeed(uint8_t id)
{
    return getSpeed(&car[id]);
}

_Bool carSwitchLanes(uint8_t id)
{
    return getSwitchLanes(&car[id]);
}

void carSetSpeed(uint8_t id, uint8_t adc)
{
    setRawSpeed(&car[id],adc);
}

void carSetSwitch(uint8_t id, _Bool sw)
{
    setRawSwitch(&car[id],sw);
}

void initCars(void)
{
    uint8_t i;
    for(i = 0; i < MAX_CARS; i++)
    {
        initCar(&car[i]);
    }
}

void setRawSpeed(hpistol usr, uint8_t adc)
{
    usr->pot_value = adc;
}

void setRawSwitch(hpistol usr, _Bool sw)
{
    usr->swPressed = sw;
}

void updateData(hpistol usr)
{
    // update the switching lanes element
    if ( usr->swAllow ) 
    {
        usr->switchLanes = usr->swPressed;
    }
    else
    {
        usr->switchLanes = false;
    }

    // update the speed
    usr->speed = usr->speed * (usr->maxSpeed - usr->acceleration)
                + usr->pot_value * usr->acceleration;
    // check if we are out of valid range
    if ( usr->speed > usr->maxSpeed ) usr->speed = usr->maxSpeed;

    // update the fuel state
    usr->fuel -= usr->fuelConsumption * usr->speed;
}

void refuel(hpistol usr)
{
    usr->fuel += usr->refuelRate;
    if ( usr->fuel > usr->maxFuel ) usr->fuel = usr->maxFuel;
}

uint8_t getSpeed(hpistol usr)
{
    return usr->speed;
}

_Bool getSwitchLanes(hpistol usr)
{
    return usr->switchLanes;
}

void initCar(hpistol usr)
{
    usr->speed = 0;
    usr->switchLanes = false;

    usr->pot_value = 0;
    usr->swPressed = false;

    usr->fuel = INIT_FUEL;
    usr->fuelConsumption = INIT_FUELCONSUMPTION;
    usr->maxFuel = INIT_MAXFUEL;
    usr->refuelRate = INIT_REFUEL;

    usr->swAllow = true;
    usr->maxSpeed = INIT_MAXSPEED;

    usr->acceleration = INIT_ACCEL;
}