#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

#define TFT_DC 9
#define TFT_CS -1
#define TFT_RST 8

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

int centerX;
int centerY;

int eyeMaxMove = 30; // 目の最大移動距離
int mouthMaxMove = 20; // 口の最大移動距離


void setup() {
  // 初期化
  tft.begin();
  tft.setRotation(3); // 必要に応じて回転を設定
  tft.fillScreen(ILI9341_BLACK); // 画面を黒でクリア

  // ディスプレイの中央を計算
  centerX = tft.width() / 2;
  centerY = tft.height() / 2;

  tft.fillScreen(ILI9341_GREEN);
}

void loop() {
  // 目と口の位置をランダムに変化させる
  int eyeOffsetX = random(-eyeMaxMove, eyeMaxMove + 1);
  int eyeOffsetY = random(-eyeMaxMove, eyeMaxMove + 1);
  int mouthOffsetX = random(-mouthMaxMove, mouthMaxMove + 1);

  // 画面クリア
  tft.fillScreen(ILI9341_GREEN);

  // 目の描画 (ディスプレイの幅に基づき中央に揃える)
  tft.fillCircle(centerX - 50 + eyeOffsetX, centerY - 40 + eyeOffsetY, 30, ILI9341_BLACK); // 左目
  tft.fillCircle(centerX + 50 + eyeOffsetX, centerY - 40 + eyeOffsetY, 30, ILI9341_BLACK); // 右目

  // 口の描画 (ディスプレイの幅に基づき中央に揃える)
  tft.fillRoundRect(centerX - 70 + mouthOffsetX, centerY + 40, 140, 30, 10, ILI9341_RED);

  // 更新間隔
  delay(500); // 0.5秒ごとに更新
}
