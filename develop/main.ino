#include <Camera.h>
#include <SPI.h>
#include <EEPROM.h>
#include <DNNRT.h>
#include "Adafruit_ILI9341.h"
#include <SDHCI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

SDClass theSD;

/* LCD Settings */
#define TFT_RST 8
#define TFT_DC  9
#define TFT_CS  10

#define DNN_IMG_W 32
#define DNN_IMG_H 32
#define CAM_IMG_W 320
#define CAM_IMG_H 240
#define CAM_CLIP_X 104
#define CAM_CLIP_Y 32
#define CAM_CLIP_W 32
#define CAM_CLIP_H 32

#define CAM_CLIP_X1 104
#define CAM_CLIP_Y1 32
#define CAM_CLIP_W1 32
#define CAM_CLIP_H1 32

#define CAM_CLIP_X2 50
#define CAM_CLIP_Y2 120
#define CAM_CLIP_W2 64
#define CAM_CLIP_H2 64

#define LINE_THICKNESS 5
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_ILI9341 tft = Adafruit_ILI9341(&SPI, TFT_DC, TFT_CS, TFT_RST);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool toggleCrop = false; // クロップ領域を切り替えるフラグ

uint8_t buf[DNN_IMG_W * DNN_IMG_H];
DNNRT dnnrt;
DNNVariable input(DNN_IMG_W * DNN_IMG_H);
static uint8_t const label[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// ボタンピン設定
const int buttonPins[] = {4, 6};
int lastButtonStates[] = {HIGH, HIGH};

int centerX = SCREEN_WIDTH / 2;
int centerY = SCREEN_HEIGHT / 2;
int eyeMaxMove = 20;
int mouthMaxMove = 5;

bool isCameraMode = false; // カメラモードのフラグ

void putStringOnLcd(String str, int color) {
  int len = str.length();
  tft.fillRect(0, 224, 320, 240, ILI9341_BLACK);
  tft.setTextSize(2);
  int sx = 160 - len / 2 * 12;
  if (sx < 0) sx = 0;
  tft.setCursor(sx, 225);
  tft.setTextColor(color);
  tft.println(str);
}

void drawBox(uint16_t* imgBuf) {
  int clipX = toggleCrop ? CAM_CLIP_X1 : CAM_CLIP_X2;
  int clipY = toggleCrop ? CAM_CLIP_Y1 : CAM_CLIP_Y2;
  int clipW = toggleCrop ? CAM_CLIP_W1 : CAM_CLIP_W2;
  int clipH = toggleCrop ? CAM_CLIP_H1 : CAM_CLIP_H2;

  for (int x = clipX; x < clipX + clipW; ++x) {
    for (int n = 0; n < LINE_THICKNESS; ++n) {
      *(imgBuf + CAM_IMG_W * (clipY + n) + x) = ILI9341_RED;
      *(imgBuf + CAM_IMG_W * (clipY + clipH - 1 - n) + x) = ILI9341_RED;
    }
  }
  for (int y = clipY; y < clipY + clipH; ++y) {
    for (int n = 0; n < LINE_THICKNESS; ++n) {
      *(imgBuf + CAM_IMG_W * y + clipX + n) = ILI9341_RED;
      *(imgBuf + CAM_IMG_W * y + clipX + clipW - 1 - n) = ILI9341_RED;
    }
  }
}


void CamCB(CamImage img) {
  if (!img.isAvailable()) {
    Serial.println("Image is not available. Try again");
    return;
  }

  CamImage small;
  CamErr err;

  // toggleCrop フラグに基づきクロップ領域を切り替える
  if (toggleCrop) {
    err = img.clipAndResizeImageByHW(small, CAM_CLIP_X1, CAM_CLIP_Y1, CAM_CLIP_X1 + CAM_CLIP_W1 - 1, CAM_CLIP_Y1 + CAM_CLIP_H1 - 1, DNN_IMG_W, DNN_IMG_H);
  } else {
    err = img.clipAndResizeImageByHW(small, CAM_CLIP_X2, CAM_CLIP_Y2, CAM_CLIP_X2 + CAM_CLIP_W2 - 1, CAM_CLIP_Y2 + CAM_CLIP_H2 - 1, DNN_IMG_W, DNN_IMG_H);
  }
  
  // 次回実行時にクロップ領域を切り替える
  toggleCrop = !toggleCrop;

  if (!small.isAvailable()) {
    putStringOnLcd("Clip and Resize Error:" + String(err), ILI9341_RED);
    return;
  }

  small.convertPixFormat(CAM_IMAGE_PIX_FMT_RGB565);
  uint16_t* tmp = (uint16_t*)small.getImgBuff();
  float* dnnbuf = input.data();
  float f_max = 0.0;

  for (int n = 0; n < DNN_IMG_H * DNN_IMG_W; ++n) {
    dnnbuf[n] = (float)((tmp[n] & 0x07E0) >> 5);
    if (dnnbuf[n] > f_max) f_max = dnnbuf[n];
  }

  for (int n = 0; n < DNN_IMG_W * DNN_IMG_H; ++n) {
    dnnbuf[n] /= f_max;
  }

  String gStrResult = "?";
  dnnrt.inputVariable(input, 0);
  dnnrt.forward();
  DNNVariable output = dnnrt.outputVariable(0);
  int index = output.maxIndex();

  if (index < 10) {
    gStrResult = String(label[index]) + String(":") + String(output[index]);
  } else {
    gStrResult = String("?:") + String(output[index]);
  }
  Serial.println(gStrResult);

  img.convertPixFormat(CAM_IMAGE_PIX_FMT_RGB565);
  uint16_t* imgBuf = (uint16_t*)img.getImgBuff();
  drawBox(imgBuf);
  tft.drawRGBBitmap(0, 0, imgBuf, 320, 224);
  putStringOnLcd(gStrResult, ILI9341_YELLOW);
}


void displayFace() {
  // 背景全体をクリアする代わりに、各パーツを再描画
  int centerX = tft.width() / 2;
  int centerY = tft.height() / 2;

  int eyeOffsetX = random(-eyeMaxMove, eyeMaxMove + 1);
  int eyeOffsetY = random(-eyeMaxMove, eyeMaxMove + 1);
  int mouthOffsetX = random(-mouthMaxMove, mouthMaxMove + 1);

  // 背景の四角形で目と口の位置をクリアする
  tft.fillRect(0, 0, 320, 240, ILI9341_GREEN);

  // 左目の描画
  tft.fillCircle(centerX - 50 + eyeOffsetX, centerY - 40 + eyeOffsetY, 30, ILI9341_BLACK);
  
  // 右目の描画
  tft.fillCircle(centerX + 50 + eyeOffsetX, centerY - 40 + eyeOffsetY, 30, ILI9341_BLACK);
  
  // 口の描画
  tft.fillRect(centerX - 70 + mouthOffsetX, centerY + 40, 140, 30, ILI9341_RED);
}



void setup() {
  Serial.begin(115200);
  pinMode(buttonPins[0], INPUT_PULLUP);
  pinMode(buttonPins[1], INPUT_PULLUP);

  tft.begin();
  tft.setRotation(3);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed");
    for (;;);
  }
  display.clearDisplay();

  while (!theSD.begin()) {
    putStringOnLcd("Insert SD card", ILI9341_RED);
  }

  File nnbfile = theSD.open("model_turu10.nnb");
  int ret = dnnrt.begin(nnbfile, 1);
  if (ret < 0) {
    putStringOnLcd("dnnrt.begin failed" + String(ret), ILI9341_RED);
    return;
  }

  theCamera.begin();
  Serial.println("Setup completed. Press button 4 to start camera processing, button 5 to display face.");
}

void loop() {
  int buttonState4 = digitalRead(buttonPins[0]);
  int buttonState6 = digitalRead(buttonPins[1]);

  if (buttonState4 == LOW && lastButtonStates[0] == HIGH) {
    Serial.println("Button 4 Pressed - Starting Camera Processing");
    isCameraMode = true; // カメラモードに設定
    theCamera.startStreaming(true, CamCB);
    delay(100);
  }

  if (buttonState6 == LOW && lastButtonStates[1] == HIGH) {
    Serial.println("Button 6 Pressed - Displaying Face");
    isCameraMode = false; // 顔表示モードに設定
    theCamera.startStreaming(false, CamCB); // ストリーミングを停止
    delay(100);
  }

  // カメラモードでないときに顔を表示
  if (!isCameraMode) {
    displayFace();
  }

  lastButtonStates[0] = buttonState4;
  lastButtonStates[1] = buttonState6;
}