#include "CppUTest/TestHarness.h"

extern "C" {
   #include "LedDriver.h"
}

static uint16_t virtualLeds;

TEST_GROUP(LedDriver)
{
   void setup()
   {
      LedDriver_Create(&virtualLeds);
   }

   void teardown()
   {

   }
};

TEST(LedDriver, LedsOffAfterCreate)
{
   virtualLeds = 0xFFFF;
   LedDriver_Create(&virtualLeds);
   LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOnLedOne)
{
   LedDriver_TurnOn(1);
   LONGS_EQUAL(1, virtualLeds);
}

TEST(LedDriver, TurnOffLedOne)
{
   LedDriver_TurnOn(1);
   LedDriver_TurnOff(1);
   LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, TurnOffMultipleLeds)
{
   LedDriver_TurnOn(8);
   LedDriver_TurnOn(9);
   LONGS_EQUAL(0x180, virtualLeds);
}

TEST(LedDriver, TurnOffAnyLed)
{
   LedDriver_TurnOn(8);
   LedDriver_TurnOn(9);
   LedDriver_TurnOff(8);
   LONGS_EQUAL(0x100, virtualLeds);
}

TEST(LedDriver, TurnOnAll)
{
   LedDriver_TurnAllOn();
   LONGS_EQUAL(0xFFFF, virtualLeds);
}

TEST(LedDriver, LedMemoryIsNotReadable)
{
   virtualLeds = 0xFFFF;
   LedDriver_TurnOn(8);
   LONGS_EQUAL(0x80, virtualLeds);
}

TEST(LedDriver, UpperAndLowerBounds)
{
   LedDriver_TurnOn(1);
   LedDriver_TurnOn(16);
   LONGS_EQUAL(0x8001, virtualLeds);
}

TEST(LedDriver, OutOfBoundsChangesNothing)
{
   LedDriver_TurnOn(-1);
   LONGS_EQUAL(0, virtualLeds);
   LedDriver_TurnOn(0);
   LONGS_EQUAL(0, virtualLeds);
   LedDriver_TurnOn(17);
   LONGS_EQUAL(0, virtualLeds);
   LedDriver_TurnOn(33);
   LONGS_EQUAL(0, virtualLeds);
   LedDriver_TurnOn(3141);
   LONGS_EQUAL(0, virtualLeds);
}

TEST(LedDriver, OutOfBoundsTurnOffDoesNoHarm)
{
   LedDriver_TurnAllOn();
   LedDriver_TurnOff(-1);
   LedDriver_TurnOff(0);
   LedDriver_TurnOff(17);
   LedDriver_TurnOff(3141);
   LONGS_EQUAL(0xFFFF, virtualLeds);
}

TEST(LedDriver, IsOn)
{
   CHECK_FALSE(LedDriver_IsOn(11));
   LedDriver_TurnOn(11);
   CHECK_TRUE(LedDriver_IsOn(11));
}

TEST(LedDriver, OutOfBoundsLedsAreAlwaysOff)
{
   CHECK_FALSE(LedDriver_IsOn(0));
   CHECK_FALSE(LedDriver_IsOn(17));
}