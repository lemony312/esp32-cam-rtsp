#include <Arduino.h>
#include <WiFi.h>

#define CAMERA_MODEL_AI_THINKER

#include "esp_camera.h"
#include "camera_pins.h"
#include "OV2640.h"

// Camera class
extern OV2640 cam;

// RTSP stuff
void initRTSP(void);
void stopRTSP(void);
