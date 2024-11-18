#include "face.h"
#include "lcd.h"

void setupFace() {}

void displayFace() {
  tft.fillRect(0, 0, 320, 240, ILI9341_GREEN);
  tft.fillCircle(160, 80, 30, ILI9341_BLACK);
  tft.fillCircle(240, 80, 30, ILI9341_BLACK);
  tft.fillRect(160, 160, 100, 20, ILI9341_RED);
}
