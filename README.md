# 📸 Selfie ESP32-CAM

## 📌 Giới thiệu
Dự án **Selfie ESP32-CAM** sử dụng module ESP32-CAM để xây dựng một hệ thống camera mini có thể:
- Chụp ảnh (selfie) từ xa qua WiFi
- Xem video stream trực tiếp trên trình duyệt
- Điều khiển thông qua giao diện web

Đây là một ứng dụng IoT đơn giản, chi phí thấp nhưng hiệu quả cao.

---

## 🎯 Mục tiêu
- Làm quen với ESP32-CAM
- Xây dựng web server nhúng
- Stream video qua WiFi
- Chụp ảnh theo yêu cầu

---

## ⚙️ Phần cứng sử dụng
- ESP32-CAM (AI Thinker)
- Camera OV2640
- USB to TTL (nạp code)

---

## 🧰 Công nghệ sử dụng
- Ngôn ngữ: C / Arduino
- IDE: Arduino IDE
- Giao thức: HTTP, WiFi
- Thư viện:
  - esp_camera.h
  - WiFi.h
  - WebServer.h

---

## 🏗️ Kiến trúc hệ thống
```
+----------------------+
|     Web Browser      |
|  (Xem / chụp ảnh)    |
+----------+-----------+
           |
        HTTP/WiFi
           |
+----------v-----------+
|     ESP32-CAM        |
|  - Camera Driver     |
|  - Web Server        |
+----------+-----------+
           |
      Camera OV2640
```

---

## 🚀 Chức năng chính
- 📡 Stream video realtime
- 📸 Chụp ảnh từ xa (selfie)
- 🌐 Truy cập qua địa chỉ IP
- ⚡ Hoạt động độc lập (không cần server ngoài)

---

## 🔧 Cài đặt

### 1. Cài Arduino IDE & ESP32 Board
- Thêm ESP32 board vào Arduino IDE

---

### 2. Kết nối ESP32-CAM

| ESP32-CAM | USB TTL |
|----------|--------|
| U0R      | TX     |
| U0T      | RX     |
| GND      | GND    |
| 5V       | 5V     |

⚠️ Lưu ý:
- Nối IO0 với GND khi nạp code
- Rút ra sau khi upload xong

---

### 3. Upload code
- Chọn board: `AI Thinker ESP32-CAM`
- Upload chương trình từ Arduino IDE

---

## ▶️ Sử dụng

1. Mở Serial Monitor
2. Kết nối WiFi
3. Lấy địa chỉ IP

Ví dụ:
```
192.168.1.100
```

4. Truy cập trình duyệt:
```
http://192.168.1.100
```

---

## 📷 Demo
- Xem video trực tiếp trên web
- Nhấn nút để chụp ảnh
- Ảnh hiển thị trên trình duyệt

---

## 📊 Ứng dụng
- Camera giám sát
- Smart home
- IoT camera
- Nhận diện khuôn mặt (mở rộng)

---

## 🚧 Hạn chế
- FPS thấp
- Chất lượng ảnh chưa cao
- Phụ thuộc WiFi
- RAM hạn chế

---

## 🔮 Hướng phát triển
- Tích hợp AI (face recognition)
- Gửi ảnh lên cloud (Firebase, MQTT)
- Viết app mobile điều khiển
- Motion detection

---

## 👨‍💻 Tác giả
- Ximon Cute

---

## 📄 License
Dự án phục vụ mục đích học tập
