#include <Globals.h>
#include <Debug.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

void getMacAddress()
{
  WiFi.macAddress(MacAddressBytes);
  mac = (int32_t)(MacAddressBytes);
  for (uint i = 0; i < sizeof(MacAddressBytes); ++i)
  {
    sprintf(MacAddress, (const char *)F("%s%02X"), MacAddress, MacAddressBytes[i]);
  }
  DebugNoLf(F("Device mac address: "));
  Debug(MacAddress);
}