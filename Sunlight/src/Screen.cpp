#include <Arduino.h>
#include <Globals.h>
#include <Config.h>
#include <Debug.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Screen.h>
#include <MacAddress.h>

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initializeOLEDDisplay()
{
  Debug(F("initializeOLEDDisplay"));
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Debug("SSD1306 allocation failed");
    while (true)
      ;
  }
  display.clearDisplay();
  display.display();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.setCursor(0, 15);
  display.print("Hello!");
  display.display();
  Debug(F("initializeOLEDDisplay done"));
}

void renderHeaderDisplay()
{
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(MacAddress);
}

void renderDisplay(char *text, uint8_t textSize)
{
  display.clearDisplay();
  renderHeaderDisplay();
  display.setTextSize(textSize);
  display.setCursor(0, 17);
  display.print(text);
  display.display();
}

