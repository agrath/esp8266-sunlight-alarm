#include <Arduino.h>
#include <Config.h>
#include <Debug.h>

void initializeSerial()
{
  #ifdef SERIAL_OUTPUT
  SERIAL_PORT.begin(115200);
  while (!SERIAL_PORT)
  {
    ; // wait for serial attach
  }
  #endif
#if DEBUG_ESP_PORT
  Serial.setDebugOutput(true);
#endif
#ifdef SERIAL_OUTPUT
  Debug();
  Debug();
  Debug(F("Initializing serial..."));
  #endif
}
