#include "Adafruit_BMP280.h"
#include "Globals.h"
#include "Debug.h"

Adafruit_BMP280 bmp;
Adafruit_Sensor *temperatureSensor = bmp.getTemperatureSensor();
int TemperatureCalibrationFactor = -2;

void initializeTemperatureSensor()
{
    if (!bmp.begin(0x76, 0x60))
    {
        Debug(F("BMP280 init failed"));
    }
    else
    {
        Debug(F("BMP280 init success"));
    }

    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

float getTemperatureReading()
{
    sensors_event_t temp_event;
    temperatureSensor->getEvent(&temp_event);
    return temp_event.temperature + TemperatureCalibrationFactor;
}
