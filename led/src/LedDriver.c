#include "LedDriver.h"

static uint16_t* ledAddress;
static uint16_t ledsImage;

enum{
    ALL_LEDS_ON = ~0,
    ALL_LEDS_OFF = ~ALL_LEDS_ON
};

enum{
    FIRST_LED = 1,
    LAST_LED = 16
};

static bool isLedOutOfBounds(uint16_t ledNumber){
    return ((ledNumber < FIRST_LED) || (ledNumber > LAST_LED));
}

static uint16_t convertLedNumberToBit(uint16_t ledNumber){
    return (1 << (ledNumber - 1));
}

static void updateHardware(void){
    *ledAddress = ledsImage;
}

static void setLedImageBit(uint16_t ledNumber){
    ledsImage |= convertLedNumberToBit(ledNumber);
}

static void clearLedImageBit(uint16_t ledNumber){
    ledsImage &= ~(convertLedNumberToBit(ledNumber));
}


void LedDriver_TurnAllOn(void){
    ledsImage = ALL_LEDS_ON;
    updateHardware();
}

void LedDriver_Create(uint16_t* address){
    ledAddress = address;
    ledsImage = ALL_LEDS_OFF;
    updateHardware();
}

void LedDriver_TurnOn(uint16_t ledNumber){
    if(isLedOutOfBounds(ledNumber))
        return;
    setLedImageBit(ledNumber);
    updateHardware();
}
void LedDriver_TurnOff(uint16_t ledNumber){
    if(isLedOutOfBounds(ledNumber))
        return;
    clearLedImageBit(ledNumber);
    updateHardware();
}

bool LedDriver_IsOn(uint16_t ledNumber){
    if(isLedOutOfBounds(ledNumber))
        return false;
    return ledsImage & convertLedNumberToBit(ledNumber);
}


