#include <WiFi.h>

// 1. Thông tin kết nối Wi-Fi (tùy chỉnh SSID và mật khẩu nếu cần)
const char* ssid = "ESP32-AP";      // Tên Wi-Fi AP
const char* password = "123456789";           // Mật khẩu Wi-Fi AP (có thể bỏ qua để tạo mạng mở)

// Thông tin mạng Wi-Fi Station (STA)
const char* ssid_sta = "YourNetworkSSID";     // SSID mạng Wi-Fi bạn muốn kết nối
const char* password_sta = "YourNetworkPass";  // Mật khẩu mạng Wi-Fi

// 2. Khởi tạo server tại cổng 80 (có thể thay đổi nếu cần)
WiFiServer server(80);

//Header for https request
String header;



// 3. Cấu hình kết nối UART (RX, TX) với STM32 (ví dụ: RX -> GPIO 16, TX -> GPIO 17)
HardwareSerial mySerial(1); // UART1

// 4. Khai báo các biến lưu trữ giá trị nhiệt độ và độ ẩm
float temperature = 0.0;
float humidity = 0.0;

// 5. Hàm để đọc dữ liệu từ STM32 qua UART
void readSensorData() {
  if (mySerial.available()) {
    String data = "";
    while (mySerial.available()) {
      char c = mySerial.read();  // Đọc từng byte dữ liệu
      data += c;
    }

    // Giả sử STM32 gửi dữ liệu theo định dạng "Temp:xx.x Humidity:yy.y"
    int tempIndex = data.indexOf("Temp:");
    int humidityIndex = data.indexOf("Humidity:");

    if (tempIndex != -1 && humidityIndex != -1) {
      temperature = data.substring(tempIndex + 5, data.indexOf(' ', tempIndex)).toFloat();
      humidity = data.substring(humidityIndex + 9).toFloat();
    }
  }
}






void setup() {
  Serial.begin(115200);    // 6. Khởi tạo Serial Monitor để debug
   // Cấu hình ESP32 ở chế độ AP + STA (Access Point và Station)
  WiFi.mode(WIFI_AP_STA);  // Chế độ AP + Station

  // Kết nối vào mạng Wi-Fi với SSID và mật khẩu
  WiFi.begin(ssid_sta, password_sta);  // ESP32 sẽ kết nối vào mạng Wi-Fi hiện có

  // 7. Cấu hình ESP32 ở chế độ Access Point
  Serial.print("Setting AP (Access Point)... ");
  WiFi.softAP(ssid, password);   // Khởi động Wi-Fi Access Point với SSID và password
  

  // Chờ cho đến khi ESP32 kết nối vào mạng Wi-Fi Station
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi. IP Address: ");
  Serial.println(WiFi.localIP());  // In ra địa chỉ IP của ESP32 khi kết nối thành công


  // 8. Lấy địa chỉ IP của ESP32 và in ra Serial Monitor
  IPAddress IP = WiFi.softAPIP();   // Địa chỉ mặc định thường là 192.168.4.1
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // 9. Bắt đầu web server
  server.begin();




  // 10. Khởi tạo UART1 để kết nối với STM32
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // UART1, baud rate 9600, RX - GPIO 16, TX - GPIO 17
}

void loop() {
  // 11. Kiểm tra có client nào kết nối không
  WiFiClient client = server.available();   // Chờ đợi client kết nối đến

  if (client) {                             // Nếu có client kết nối,
    Serial.println("New Client.");          // In thông báo ra Serial Monitor
    String currentLine = "";                // Tạo biến lưu dữ liệu nhận từ client

    while (client.connected()) {            // Vòng lặp khi client đang kết nối
      if (client.available()) {             // Kiểm tra có dữ liệu từ client
        char c = client.read();             // Đọc từng byte dữ liệu
        Serial.write(c);                    // In dữ liệu ra Serial Monitor (tùy chọn)
        currentLine += c;

        // 12. Kiểm tra khi kết thúc dòng mới (hết yêu cầu HTTP)
        if (c == '\n') {                    
          if (currentLine.length() == 2) {  // Khi dòng trống là kết thúc yêu cầu HTTP
            // 13. Gửi phản hồi HTTP với mã và tiêu đề
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // 14. Gửi nội dung HTML (phần tùy chỉnh để viết mã HTML của bạn)
            client.println("<html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
            client.println("<body><h1>Sensor Data</h1>");
            client.println("<p>Temperature: " + String(temperature) + " °C</p>");
            client.println("<p>Humidity: " + String(humidity) + " %</p>");
            client.println("</body></html>");

            client.println(); // Kết thúc phản hồi HTTP với dòng trống
            break;            // Thoát khỏi vòng lặp sau khi gửi phản hồi
          } else { 
            currentLine = ""; // Đặt lại dòng hiện tại nếu gặp newline
          }
        } else if (c != '\r') {  // Nếu không phải ký tự xuống dòng, lưu vào biến
          currentLine += c;
        }
      }
    }

    //  15. Đọc dữ liệu từ STM32 (dữ liệu cảm biến) khi có client
    readSensorData();
    // 16. Đóng kết nối khi phản hồi xong
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

  
}
