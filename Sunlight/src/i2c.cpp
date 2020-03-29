#include <Arduino.h>
#include <Wire.h>
#include <Debug.h>
#include <Screen.h>
#include <Globals.h>

bool recoveryAttempted = false;

void initializeI2C()
{
  Wire.begin();
#ifdef ESP32
  Wire.setClock(800000);
#endif
#ifdef ESP8266
  Wire.setClock(400000);
#endif
}

void recoverI2C()
{
  Debug("...Starting I2C bus recovery");
  delay(200);
  //try i2c bus recovery at 100kHz = 5uS high, 5uS low
  pinMode(SDA, OUTPUT); //keeping SDA high during recovery
  digitalWrite(SDA, HIGH);
  pinMode(SCL, OUTPUT);
  for (int i = 0; i < 10; i++)
  { //9nth cycle acts as NACK
    digitalWrite(SCL, HIGH);
    delayMicroseconds(5);
    digitalWrite(SCL, LOW);
    delayMicroseconds(5);
  }

  //a STOP signal (SDA from low to high while CLK is high)
  digitalWrite(SDA, LOW);
  delayMicroseconds(5);
  digitalWrite(SCL, HIGH);
  delayMicroseconds(2);
  digitalWrite(SDA, HIGH);
  delayMicroseconds(2);
  //bus status is now : FREE

  Debug("...I2C bus recovery done, starting scan in 2 secs");
  //return to power up mode
  pinMode(SDA, INPUT);
  pinMode(SCL, INPUT);
  delay(2000);
}

int debugScanForI2CDevices()
{
  Debug(F("Scanning for I2C devices..."));
  int errorCount = 0;
  int deviceCount = 0;
  for (byte address = 1; address < 127; address++)
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0)
    {
      DebugF((const char *)F("... I2C device found at address 0x%02X\r\n"), address);
      deviceCount++;

      if (address == 0x3C)
      {
        Debug(" ... Screen");
        HAS_SCREEN = true;
      }
    //   else if (address == 0x40)
    //   {
    //     Debug(" ... Current Sensor");
    //     HAS_CURRENT_SENSOR = true;
    //   }
    }
    else if (error == 4)
    {
      DebugF((const char *)F("...Unknown error at address 0x%02X\r\n"), address);
      errorCount++;
    }
  }

  if (deviceCount == 0 && errorCount == 0)
  {
    Debug(F("...No I2C devices found\r\n"));
    return deviceCount;
  }
  else if (deviceCount == 0 && errorCount == 126)
  {
    //all addresses returned error==4
    if (!recoveryAttempted)
    {
      Debug("... I2C bus is in an error state.");
      recoveryAttempted = true;
      recoverI2C();
      Debug("... I2C bus recovery complete.");
      initializeI2C();
      ESP.restart();
      return debugScanForI2CDevices();
    }
  }

  Debug(F("...I2C scan complete\r\n"));
  DebugF("... DeviceCount: %d, ErrorCount: %d, Recovery attempted: %s\r\n", deviceCount, errorCount, recoveryAttempted ? "Yes" : "No");
  return deviceCount;
}
