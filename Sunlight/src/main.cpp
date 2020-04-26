#include <Arduino.h>
#define GLOBALS 1 //only do this in a single file
#include <Globals.h>
#include <Wire.h>
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
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>
#include <Led.h>
#include <ntp.h>
#include <TimeHelper.h>

//hardcode alarm time and work out pattern for wake up
//later (when i have a screen and encoder)
//bedside light
//menu for config
//sleep
//alarm time config
//show stuff like temp and time
//traffic display?
//sleep monitor using accel?
void setupAlarms();
//void testAlarmCallback();
void testSunriseEffect();

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

  initializeLED();

  initWifi();
  connectToWifi();

  getUtcFromNtp();

  //todo: needs to be moved to flash config (menu)
  //setupAlarms();
}

//todo: needs to be an array of multiple alarms
AlarmData alarm;
void setupAlarms()
{
  //Saturday & Sunday
  time_t alarmTime = CreateTimeFromHourMinuteSecond(19, 45, 0);
  time_t wakePeriod = CreateTimeFromHourMinuteSecond(0, 30, 0);
  //time_t triggerTime = alarmTime - wakePeriod;

  alarm.AlarmTime = alarmTime;
  alarm.Days = GetFlagValueForDayOfWeek(dowSaturday) | GetFlagValueForDayOfWeek(dowTuesday);
  alarm.WakePeriod = wakePeriod;

  //todo: consider how we are going to handle overlapping alarms (validation?)
}

void loop()
{
  //DebugF("Current temperature %f\r\n", getTemperatureReading());
  //delay(1000);
  //pulseLEDsForTesting();
  delay(50);
  testSunriseEffect();
  // Test alarm trigger
  // struct tm *localTime = getCurrentLocalTime();
  // if(CheckAlarm(&alarm, localTime) && !alarm.IsInProgress)
  // {
  //   alarm.IsInProgress = true;
  // }
}

int step = 0;
void testSunriseEffect()
{

  
  if (step > 510)
  {
    step = 0;
  }

  DebugF("[testSunriseEffect] step %d\r\n", step);
  
  CRGB ringColor = getCurrentRingSunriseColor(step);
  CRGB coreColor = getCurrentCoreSunriseColor(step);

  //ring
  fill_solid(leds, NUM_LEDS, ringColor);
  FastLED.show();

  //core
  sendPixieColor(coreColor);

  step++;
}

// byte brightness = 0;
// int direction = 1;
// void pulseLEDsForTesting(){

//   brightness += direction;
//   if (brightness == 255 || brightness == 0)
//   {
//     direction *= -1;
//   }

//   byte gammaCorrectedBrightness = GammaCorrection[brightness];
//   CRGB color = CRGB(gammaCorrectedBrightness, gammaCorrectedBrightness, gammaCorrectedBrightness);
//   fill_solid(leds, NUM_LEDS, color);
//   FastLED.show();
//   sendPixieColor(color);

//   //DebugF("brightness %d=>%d (%d)\r\n", brightness, gammaCorrectedBrightness, direction);
//   delay(20);
//   yield();
// }