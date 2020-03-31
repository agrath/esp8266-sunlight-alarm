#include <Arduino.h>
#define GLOBALS 1 //only do this in a single file
#include <Globals.h>
#include <Wire.h>
#include <FastLED.h>
#include <Config.h>
#include <Debug.h>
#include <i2c.h>
#include <Serial.h>
#include <Screen.h>
#include <MacAddress.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <Temperature.h>
#ifdef ESP8266
#include <ESP8266httpUpdate.h>
#else
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#endif
#include <WiFi.h>

CRGB leds[NUM_LEDS];
char gammaCorrection[] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2,
        2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5,
        5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
        10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
        17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
        25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
        37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
        51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
        69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
        90, 92, 93, 95, 96, 98, 99, 101, 102, 104, 105, 107, 109, 110, 112, 114,
        115, 117, 119, 120, 122, 124, 126, 127, 129, 131, 133, 135, 137, 138, 140, 142,
        144, 146, 148, 150, 152, 154, 156, 158, 160, 162, 164, 167, 169, 171, 173, 175,
        177, 180, 182, 184, 186, 189, 191, 193, 196, 198, 200, 203, 205, 208, 210, 213,
        215, 218, 220, 223, 225, 228, 231, 233, 236, 239, 241, 244, 247, 249, 252, 255};

//ntp init code
//led init code
//pixie init code
//test led ring
//test pixie
//hardcode alarm time and work out pattern for wake up
//later (when i have a screen and encoder)
//bedside light
//menu for config
//sleep
//alarm time config
//show stuff like temp and time
//traffic display?
//sleep monitor using accel?

void setup()
{
  if (debugEnabled)
  {
    initializeSerial();
  }

  initializeI2C();

  Debug("Hello world!");

  int deviceCount = debugScanForI2CDevices();
  if (deviceCount == 0)
  {
    while (true)
    {
      Debug(F("Startup halted after I2C bus initialization for debugging..."));
      delay(1000);
    }
  }
  if (HAS_SCREEN)
  {
    initializeOLEDDisplay();
  }
  if (HAS_TEMP_SENSOR)
  {
    initializeTemperatureSensor();
  }

  initWifi();
  connectToWifi();
}

void loop()
{
  DebugF("Current temperature %f\r\n", getTemperatureReading());
  delay(1000);
}
