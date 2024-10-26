let eyeX, eyeY; // 目の中心座標
let mouthX, mouthY; // 口の中心座標
let maxEyeMove = 40; // 目の最大移動距離
let maxMouthMove = 10; // 口の最大移動距離
let maxEarMove = 20; // 耳の最大移動距離
let maxWhiskerMove = 15; // ひげの最大移動距離

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
  let earOffsetX = constrain(mouseX - width / 2, -maxEarMove, maxEarMove);
  let earOffsetY = constrain(mouseY - height / 2, -maxEarMove, maxEarMove);
  let whiskerOffsetX = constrain(mouseX - width / 2, -maxWhiskerMove, maxWhiskerMove);
  let whiskerOffsetY = constrain(mouseY - height, -maxWhiskerMove, maxWhiskerMove);

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
  line(mouthPosX - 20, mouthPosY, mouthPosX + 20, mouthPosY); // 口

  // 猫耳の位置
  let earLeftX = eyeX - 60 + earOffsetX;
  let earRightX = eyeX + 60 + earOffsetX;
  let earY = eyeY - 80 + earOffsetY;

  // 猫耳の描画
  fill(0, 0, 0); // ピンク色
  noStroke();
  triangle(earLeftX - 20, earY + 30, earLeftX, earY, earLeftX + 20, earY + 30); // 左耳
  triangle(earRightX - 20, earY + 30, earRightX, earY, earRightX + 20, earY + 30); // 右耳

  // ひげの位置
  let whiskerLeftX = mouthX - 50 + whiskerOffsetX;
  let whiskerRightX = mouthX + 50 + whiskerOffsetX;
  let whiskerY = mouthY + whiskerOffsetY;

  // ひげの描画
  stroke(0);
  strokeWeight(3);
  // 左ひげ
  line(whiskerLeftX, whiskerY - 10, whiskerLeftX - 30, whiskerY - 20); // 上
  line(whiskerLeftX, whiskerY, whiskerLeftX - 30, whiskerY); // 中
  line(whiskerLeftX, whiskerY + 10, whiskerLeftX - 30, whiskerY + 20); // 下

  // 右ひげ
  line(whiskerRightX, whiskerY - 10, whiskerRightX + 30, whiskerY - 20); // 上
  line(whiskerRightX, whiskerY, whiskerRightX + 30, whiskerY); // 中
  line(whiskerRightX, whiskerY + 10, whiskerRightX + 30, whiskerY + 20); // 下
}

