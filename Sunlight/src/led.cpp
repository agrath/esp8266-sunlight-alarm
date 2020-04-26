#include <Debug.h>
#include <Config.h>
#include <Globals.h>
#include <FastLED.h>
#include <led.h>

//todo: ring intensity by turning leds in the ring off?
//vary intensity by starting with the ring of 24 pixels only
//100000100000100000100000  00
//110000110000110000110000  00
//111000111000111000111000  00
//111100111100111100111100  00
//111110111110111110111110  00
//111111111111111111111111  00
//                          ..
//111111111111111111111111  FF

//use setBrightness through the loop too
//call show() frequently for temporaral dithering if setBrightness < 255

//can't be in globals because GLOBALEXTERN gets overridden by the initializer
extern const TProgmemRGBPalette16 SunrisePalette PROGMEM =
{
    0x210000, 0x600400, 0x7e0800, 0x9d0d00, 
    0xbb0f00, 0xdb1500, 0xf61a00, 0xf72d00, 
    0xf74700, 0xf66500, 0xf6a003, 0xf5bf08, 
    0xf69f03, 0xf4c008, 0xf4df0e, 0xf4f71e
};

CRGB getCurrentRingSunriseColor(uint16_t step)
{
    //uint16 can go up to 65535 so we just clamp it to 512
    step = constrain(step, 0, 510);
    //so from 0-255 we want to have travelled half of the palette and all of the brightness (for the ring)
    uint8_t brightness = constrain(step, 0, 255); //so at >255 brightness is clamped at 255
    uint8_t index = step / 2;                     //by 255, index = 128, by 512, index = 255

    DebugF("[testSunriseEffect] ring index:%d, brightness:%d\r\n", index, brightness);
    //use step as both palette and brightness
    CRGB pixelColor = ColorFromPalette(SunrisePalette, index, brightness, LINEARBLEND);
    return pixelColor;
}
CRGB getCurrentCoreSunriseColor(uint16_t step)
{
    //uint16 can go up to 65535 so we just clamp it to 510
    step = constrain(step, 0, 510);
    //the core doesn't ignite until halfway through the sequence
    if (step < 255)
    {
        DebugF("[testSunriseEffect] core index:0, brightness:0\r\n");
        return CRGB::Black;
    }
    //after 255
    //core only ignites when we are >128 colours in
    uint8_t index = step / 2;        //by 255, index = 128, by 510, index = 255
    uint8_t brightness = step - 255; //at 255 this is 0, then by 510 this becomes 255

    DebugF("[testSunriseEffect] core index:%d, brightness:%d\r\n", index, brightness);
    //use step as both palette and brightness
    CRGB pixelColor = ColorFromPalette(SunrisePalette, index, brightness, LINEARBLEND);
    return pixelColor;
}

void initializeLED()
{
    Debug(F("initializeLED"));

    //pinMode(INTERNAL_LED_DATA_PIN, OUTPUT);
    //pinMode(EXTERNAL_LED_DATA_PIN, OUTPUT);

    FastLED.addLeds<WS2811, EXTERNAL_LED_DATA_PIN, GRB>(leds, NUM_LEDS);
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