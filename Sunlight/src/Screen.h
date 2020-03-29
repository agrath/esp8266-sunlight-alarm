#include <Arduino.h>
#include <MacAddress.h>

void initializeOLEDDisplay();
void renderHeaderDisplay();
void renderDisplay(char *text, uint8_t textSize);
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels