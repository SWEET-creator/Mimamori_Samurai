#include "TensorFlowLite.h"
#include "yolo11n_float16.h"  // 先ほど作成したモデルのヘッダーファイル

// モデルのバッファサイズを定義
const int kModelArenaSize = 4096;
const int kTensorArenaSize = 1024;
uint8_t tensor_arena[kTensorArenaSize];

void setup() {
  Serial.begin(115200);
  // TFLite Micro初期化
  tflite::MicroErrorReporter error_reporter;
  tflite::AllOpsResolver resolver;
  tflite::MicroInterpreter interpreter(model, resolver, tensor_arena, kTensorArenaSize, &error_reporter);
  interpreter.AllocateTensors();

  // 入力テンソルの取得
  TfLiteTensor* input = interpreter.input(0);
  input->data.f[0] = 1.0f;  // 入力値を設定

  // 推論実行
  if (interpreter.Invoke() != kTfLiteOk) {
    Serial.println("Error during inference");
    return;
  }

  // 出力テンソルの取得と表示
  TfLiteTensor* output = interpreter.output(0);
  Serial.print("Output: ");
  Serial.println(output->data.f[0]);
}

void loop() {
  // ループ内では処理なし
}