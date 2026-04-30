#include "esp_camera.h"
#include <WiFi.h>
#include <HTTPClient.h>

// === CHỈ SỬA 3 DÒNG NÀY ===
const char* ssid     = "Hieu Cute";
const char* password = "ximon123";
const char* pcIP     = "192.168.76.155";   // IP MÁY TÍNH (ipconfig)
// ===========================

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

bool isShooting = false;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
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

  // CẤU HÌNH SIÊU TỐI ƯU CHO 3 ẢNH/GIÂY
  config.frame_size = FRAMESIZE_XGA;     // 1024x768 (rất nét + nhanh)
  config.jpeg_quality = 12;             // 12 = cân bằng nét + tốc độ
  config.fb_count = 2;
  config.grab_mode = CAMERA_GRAB_LATEST;

  esp_camera_init(&config);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println("\nWiFi OK - IP: " + WiFi.localIP().toString());

  server.begin();
  Serial.println("Server dieu khien san sang!");
}

void captureAndSend() {
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) return;

  HTTPClient http;
  http.begin("http://" + String(pcIP) + ":8888/upload");
  http.addHeader("Content-Type", "image/jpeg");
  http.POST(fb->buf, fb->len);
  http.end();
  esp_camera_fb_return(fb);
}

void loop() {
  // Nhận lệnh từ Python
  WiFiClient client = server.available();
  if (client) {
    String req = client.readStringUntil('\r');
    if (req.indexOf("/shoot") != -1) isShooting = true;
    if (req.indexOf("/stop") != -1)  isShooting = false;
    client.println("HTTP/1.1 200 OK\r\n\r\nOK");
    client.stop();
  }

  if (isShooting) {
    captureAndSend();
    delay(280);  // ~3.3 ảnh/giây (280ms + thời gian gửi ≈ 330ms)
  }
}