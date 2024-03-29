#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdint.h>
#include <stdbool.h>


void LedDriver_Create(uint16_t* address);
void LedDriver_TurnOn(uint16_t ledNumber);
void LedDriver_TurnOff(uint16_t ledNumber);
void LedDriver_TurnAllOn(void);
bool LedDriver_IsOn(uint16_t ledNumber);

#endif