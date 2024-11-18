#include "camera.h"
#include "lcd.h"
#include "config.h"

extern DNNRT dnnrt;
extern DNNVariable input;

bool toggleCrop = false;

void setupCamera() {
  theCamera.begin();
}

void startCameraProcessing() {
  theCamera.startStreaming(true, CamCB);
}

void stopCameraProcessing() {
  theCamera.startStreaming(false, CamCB);
}

void CamCB(CamImage img) {
  if (!img.isAvailable()) {
    Serial.println("Image is not available. Try again");
    return;
  }

  CamImage small;
  CamErr err;

  if (toggleCrop) {
    err = img.clipAndResizeImageByHW(small, CAM_CLIP_X, CAM_CLIP_Y, CAM_CLIP_X + CAM_CLIP_W - 1, CAM_CLIP_Y + CAM_CLIP_H - 1, DNN_IMG_W, DNN_IMG_H);
  } else {
    err = img.clipAndResizeImageByHW(small, CAM_CLIP_X, CAM_CLIP_Y, CAM_CLIP_X + CAM_CLIP_W - 1, CAM_CLIP_Y + CAM_CLIP_H - 1, DNN_IMG_W, DNN_IMG_H);
  }
  toggleCrop = !toggleCrop;

  if (!small.isAvailable()) {
    putStringOnLcd("Clip and Resize Error:" + String(err), ILI9341_RED);
    return;
  }
  
  small.convertPixFormat(CAM_IMAGE_PIX_FMT_RGB565);
  float* dnnbuf = input.data();
  float f_max = 0.0;

  for (int n = 0; n < DNN_IMG_W * DNN_IMG_H; ++n) {
    dnnbuf[n] = (float)((small.getImgBuff()[n] & 0x07E0) >> 5);
    if (dnnbuf[n] > f_max) f_max = dnnbuf[n];
  }
  
  for (int n = 0; n < DNN_IMG_W * DNN_IMG_H; ++n) {
    dnnbuf[n] /= f_max;
  }

  dnnrt.inputVariable(input, 0);
  dnnrt.forward();
  putStringOnLcd("Processing Done", ILI9341_YELLOW);
}
