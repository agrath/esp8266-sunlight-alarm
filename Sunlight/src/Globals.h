#include <Arduino.h>
#include <IpAddress.h>
#include <FastLED.h>
#include <Config.h>

//http://www.wellho.net/mouth/2575_Sharing-variables-between-files-of-code-in-C-extern.html

#ifdef GLOBALS
#define GLOBALEXTERN
#else
#define GLOBALEXTERN extern
#endif

//note: you can't set defaults on these, per https://stackoverflow.com/a/33464365 even though I like cake
GLOBALEXTERN uint8_t MacAddressBytes[6];
GLOBALEXTERN char MacAddress[13];
GLOBALEXTERN int32_t mac;
GLOBALEXTERN bool HAS_SCREEN;
GLOBALEXTERN bool HAS_TEMP_SENSOR;
GLOBALEXTERN double temperature;
GLOBALEXTERN double humidity;
GLOBALEXTERN IPAddress ip;
GLOBALEXTERN bool wasWifiConnected;
GLOBALEXTERN bool isWifiConnected;
GLOBALEXTERN CRGB leds[NUM_LEDS];
GLOBALEXTERN bool timeCallbackInvoked;
GLOBALEXTERN timeval utcVal;
GLOBALEXTERN time_t utc;
GLOBALEXTERN char sharedCharacterBuffer[128]; //generic buffer