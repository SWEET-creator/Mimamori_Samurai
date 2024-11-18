#include "lcd.h"
#include "config.h"

Adafruit_ILI9341 tft(&SPI, TFT_DC, TFT_CS, TFT_RST);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setupLCD() {
  tft.begin();
  tft.setRotation(3);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed");
    for (;;);
  }
  display.clearDisplay();
}

void putStringOnLcd(String str, int color) {
  tft.fillRect(0, 224, 320, 240, ILI9341_BLACK);
  tft.setTextSize(2);
  tft.setCursor((160 - str.length() / 2 * 12), 225);
  tft.setTextColor(color);
  tft.println(str);
}
