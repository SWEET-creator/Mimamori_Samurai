#include "config.h"
#include "lcd.h"
#include "camera.h"
#include "face.h"
#include <SDHCI.h>
#include <DNNRT.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_SSD1306.h>

bool isCameraMode = false;
DNNRT dnnrt;
SDClass theSD;
DNNVariable input(DNN_IMG_W * DNN_IMG_H);

// ボタン設定
const int buttonPins[] = {4, 6};
int lastButtonStates[] = {HIGH, HIGH};

void setup() {
  Serial.begin(CONSOLE_BAUDRATE);
  setupLCD();
  setupCamera();
  setupFace();

  // DNNモデルの初期化
  while (!theSD.begin()) {
    putStringOnLcd("Insert SD card", ILI9341_RED);
  }

  File nnbfile = theSD.open("model_turu10.nnb");
  int ret = dnnrt.begin(nnbfile, 1);
  if (ret < 0) {
    putStringOnLcd("dnnrt.begin failed" + String(ret), ILI9341_RED);
    return;
  }

  Serial.println("Setup completed.");
}

void loop() {
  int buttonState4 = digitalRead(buttonPins[0]);
  int buttonState6 = digitalRead(buttonPins[1]);

  if (buttonState4 == LOW && lastButtonStates[0] == HIGH) {
    Serial.println("Button 4 Pressed - Starting Camera Processing");
    isCameraMode = true;
    startCameraProcessing();
    delay(100);
  }

  if (buttonState6 == LOW && lastButtonStates[1] == HIGH) {
    Serial.println("Button 6 Pressed - Displaying Face");
    isCameraMode = false;
    stopCameraProcessing();
    displayFace();
    delay(100);
  }

  lastButtonStates[0] = buttonState4;
  lastButtonStates[1] = buttonState6;
}
