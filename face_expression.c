#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int centerX = SCREEN_WIDTH / 2;
int centerY = SCREEN_HEIGHT / 2;

int eyeMaxMove = 10; // 目の最大移動距離
int mouthMaxMove = 5; // 口の最大移動距離

void setup() {
  // 初期化
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    for(;;);
  }

  display.clearDisplay();
}

void loop() {
  // マウスに追従する位置をランダムにシミュレート
  int mouseX = random(0, SCREEN_WIDTH);
  int mouseY = random(0, SCREEN_HEIGHT);

  // 目と口の位置計算
  int eyeOffsetX = constrain(mouseX - centerX, -eyeMaxMove, eyeMaxMove);
  int eyeOffsetY = constrain(mouseY - centerY, -eyeMaxMove, eyeMaxMove);
  int mouthOffsetX = constrain(mouseX - centerX, -mouthMaxMove, mouthMaxMove);

  // 目の描画
  display.clearDisplay();
  display.drawLine(centerX - 20 + eyeOffsetX, centerY - 10 + eyeOffsetY,
                   centerX - 20 + eyeOffsetX, centerY + 10 + eyeOffsetY, WHITE);
  display.drawLine(centerX + 20 + eyeOffsetX, centerY - 10 + eyeOffsetY,
                   centerX + 20 + eyeOffsetX, centerY + 10 + eyeOffsetY, WHITE);

  // 口の描画
  display.drawLine(centerX - 20 + mouthOffsetX, centerY + 20,
                   centerX + 20 + mouthOffsetX, centerY + 20, WHITE);

  // 表示更新
  display.display();

  delay(500); // 0.5秒ごとに更新
}
