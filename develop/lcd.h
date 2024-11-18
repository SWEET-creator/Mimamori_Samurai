#ifndef LCD_H
#define LCD_H

#include <Adafruit_ILI9341.h>
#include <Adafruit_SSD1306.h>

void setupLCD();
void putStringOnLcd(String str, int color);

#endif // LCD_H
