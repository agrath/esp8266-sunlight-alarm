#include <Debug.h>
#include <Config.h>
#include <Globals.h>
#include <FastLED.h>
#include <led.h>

void initializeLED()
{
    Debug(F("initializeLED"));

    //pinMode(INTERNAL_LED_DATA_PIN, OUTPUT);
    //pinMode(EXTERNAL_LED_DATA_PIN, OUTPUT);

    FastLED.addLeds<WS2811, EXTERNAL_LED_DATA_PIN, RGB>(leds, NUM_LEDS);
    //FastLED.addLeds<WS2811, INTERNAL_LED_DATA_PIN, GRB>(leds, NUM_LEDS);

    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();

    Serial1.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY, 2);
    sendPixieColor(CRGB::Black);
}

void sendPixieColor(CRGB color)
{
    byte pixieBuffer[3] = {0x00, 0x00, 0x00};
    pixieBuffer[0] = color.r;
    pixieBuffer[1] = color.g;
    pixieBuffer[2] = color.b;
    Serial1.write(pixieBuffer, 3);
    Serial1.flush();
}