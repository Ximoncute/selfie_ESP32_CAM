import threading
import http.server
import socketserver
import requests
import os
from datetime import datetime

SAVE_FOLDER = r"C:\Users\Admin\Desktop\test\DO_AN_TOT_NGHIEP_ANH_QUYEN\image"
os.makedirs(SAVE_FOLDER, exist_ok=True)

ESP_IP = "192.168.76.92"        # ← IP ESP32-CAM của bạn
shooting = False               # Trạng thái chụp

class Handler(http.server.SimpleHTTPRequestHandler):
    def do_POST(self):
        if self.path == '/upload':
            length = int(self.headers['Content-Length'])
            data = self.rfile.read(length)
            fname = datetime.now().strftime("%Y%m%d_%H%M%S_%f")[:-3] + ".jpg"
            open(os.path.join(SAVE_FOLDER, fname), "wb").write(data)
            print(f"ĐÃ LƯU: {fname}  ({len(data)/1024:.1f} KB)")
            self.send_response(200)
            self.end_headers()
            self.wfile.write(b"OK")

threading.Thread(target=lambda: socketserver.TCPServer(("", 8888), Handler).serve_forever(), daemon=True).start()

print("="*60)
print("     ESP32-CAM CHỤP NHANH 3 ẢNH/GIÂY (1024x768)")
print("     Gõ 1 + Enter → Bắt đầu chụp")
print("     Gõ 0 + Enter → Dừng ngay lập tức")
print("="*60)

while True:
    cmd = input("\nNhập lệnh (1 = bắt đầu chụp, 0 = dừng): ").strip()
    try:
        if cmd == "1" and not shooting:
            requests.get(f"http://{ESP_IP}/shoot", timeout=5)
            shooting = True
            print("BẮT ĐẦU CHỤP – ảnh về ngay lập tức!")
        elif cmd == "0" and shooting:
            requests.get(f"http://{ESP_IP}/stop", timeout=5)
            shooting = False
            print("ĐÃ DỪNG CHỤP!")
        elif cmd == "1" and shooting:
            print("Đang chụp rồi! Gõ 0 để dừng")
        elif cmd == "0" and not shooting:
            print("Đã dừng rồi! Gõ 1 để chụp")
        else:
            print("Chỉ gõ 1 hoặc 0 thôi!")
    except:
        print("Không kết nối được ESP32-CAM – kiểm tra WiFi/IP")