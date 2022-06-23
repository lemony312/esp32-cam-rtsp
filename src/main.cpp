#include "main.h"
#include "wifikeys.h"

camera_config_t initCameraConfig() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  framesize_t frameSize = FRAMESIZE_VGA;
  if(psramFound()){
    config.frame_size = frameSize;
    config.jpeg_quality = 8;
    config.fb_count = 2;
  } else {
    config.frame_size = frameSize;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  return config;
}

void connectToWifi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(". trying");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}


/** Camera class */
OV2640 cam;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println(); 

	Serial.println("\n\n##################################");
	Serial.printf("Internal Total heap %d, internal Free Heap %d\n", ESP.getHeapSize(), ESP.getFreeHeap());
	Serial.printf("SPIRam Total heap %d, SPIRam Free Heap %d\n", ESP.getPsramSize(), ESP.getFreePsram());
	Serial.printf("ChipRevision %d, Cpu Freq %d, SDK Version %s\n", ESP.getChipRevision(), ESP.getCpuFreqMHz(), ESP.getSdkVersion());
	Serial.printf("Flash Size %d, Flash Speed %d\n", ESP.getFlashChipSize(), ESP.getFlashChipSpeed());
	Serial.println("##################################\n\n");

  delay(100);
	cam.init(initCameraConfig());
	delay(100);

  // infinitly waits
  connectToWifi();
  IPAddress ip = WiFi.localIP();
  Serial.print("Camera Ready! Use 'http://");
  Serial.print(ip);
  Serial.println("' to connect");

  Serial.print("Stream Link: rtsp://");
	Serial.print(ip);
	Serial.println(":8554/mjpeg/1\n");


  initRTSP();
}

void loop() {
  
}