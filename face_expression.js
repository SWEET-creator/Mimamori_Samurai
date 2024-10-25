let eyeX, eyeY; // 目の中心座標
let mouthX, mouthY; // 口の中心座標
let maxEyeMove = 30; // 目の最大移動距離
let maxMouthMove = 10; // 口の最大移動距離

function setup() {
  createCanvas(400, 400);
  // 初期位置
  eyeX = width / 2;
  eyeY = height / 2 - 50;
  mouthX = width / 2;
  mouthY = height / 2 + 50;
}

function draw() {
  background(220);

  // マウスに対する相対位置
  let eyeOffsetX = constrain(mouseX - width / 2, -maxEyeMove, maxEyeMove);
  let eyeOffsetY = constrain(mouseY - height / 2, -maxEyeMove, maxEyeMove);
  let mouthOffsetX = constrain(mouseX - width / 2, -maxMouthMove, maxMouthMove);
  let mouthOffsetY = constrain(mouseY - height / 2, -maxMouthMove, maxMouthMove);

  // 目の位置
  let eyeLeftX = eyeX - 30 + eyeOffsetX;
  let eyeRightX = eyeX + 30 + eyeOffsetX;
  let eyeYPos = eyeY + eyeOffsetY;

  // 目の描画
  stroke(0);
  strokeWeight(8);
  line(eyeLeftX, eyeYPos - 20, eyeLeftX, eyeYPos + 20); // 左目
  line(eyeRightX, eyeYPos - 20, eyeRightX, eyeYPos + 20); // 右目

  // 口の位置
  let mouthPosX = mouthX + mouthOffsetX;
  let mouthPosY = mouthY + mouthOffsetY;

  // 口の描画
  strokeWeight(5);
  line(mouthPosX - 40, mouthPosY, mouthPosX + 40, mouthPosY); // 口
}
