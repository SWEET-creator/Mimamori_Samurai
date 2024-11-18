#ifndef CONFIG_H
#define CONFIG_H

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

#define CONSOLE_BAUDRATE 115200
#define RECEIVE_PACKET_SIZE 1500

#define  AP_SSID        "linksys"
#define  PASSPHRASE     "0123456789"

#define  HTTP_SRVR_IP  "192.168.1.100"
#define  HTTP_PORT     "10080"
#define  HTTP_GET_PATH "/"
#define  HTTP_POST_PATH "/postData"

#endif // CONFIG_H
