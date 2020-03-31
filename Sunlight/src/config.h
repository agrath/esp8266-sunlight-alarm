#include "credentials.h"
#ifndef CONFIG_H

#define CONFIG_H
#define NUM_LEDS 24

#ifdef ESP8266
#define EXTERNAL_LED_DATA_PIN 5 //D6 ring led
#define INTERNAL_LED_DATA_PIN 7 //D7 internal led
#elif defined(ESP32)
#define EXTERNAL_LED_DATA_PIN 17
#define INTERNAL_LED_DATA_PIN 16
#endif

#define SERIAL_OUTPUT true
const bool debugEnabled = true;

const char HardcodedWifi_SSID[] = WIFI_SSID;
const char HardcodedWifi_Password[] = WIFI_PASSWORD;

#endif