#include <Temperature_LM75_Derived.h>

NXP_LM75A temperatureSensor;

float getTemperatureReading()
{
    return temperatureSensor.readTemperatureC();
}
