#ifndef CAMERA_H
#define CAMERA_H

#include <Camera.h>
#include <DNNRT.h>

void setupCamera();
void startCameraProcessing();
void stopCameraProcessing();
void CamCB(CamImage img);

#endif // CAMERA_H
