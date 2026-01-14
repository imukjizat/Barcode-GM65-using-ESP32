#include <WiFi.h>
#include <HTTPClient.h>

const char* WIFI_SSID = "JXXXXX";
const char* WIFI_PASS = "semiskinitu?";

const char* API_URL = "https://iot.sindangraja.com/api/cart/add";

// ===== GM65 UART =====
HardwareSerial BarcodeSerial(2);
#define GM65_RX 34
#define GM65_TX 32

String buffer = "";
unsigned long lastCharTime = 0;
const unsigned long MSG_TIMEOUT = 60;

// ===== Kirim ke API =====
void sendToServer(const String &barcode) {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi tidak terhubung");
    return;
  }

  HTTPClient http;
  http.begin(API_URL);
  http.addHeader("Content-Type", "application/json");

  String body =
    "{\"device_id\":\"IOT-01\","
    "\"barcode\":\"" + barcode + "\"}";

  Serial.println("\n=== KIRIM API ===");
  Serial.println(body);

  int code = http.POST(body);
  String res = http.getString();

  Serial.printf("HTTP %d\n", code);
  Serial.println(res);

  http.end();
}

// ===== Proses barcode =====
void processBarcode() {
  buffer.trim();
  if (buffer.length() == 0) return;

  Serial.print("BARCODE: ");
  Serial.println(buffer);

  sendToServer(buffer);

  buffer = "";
}

void setup() {
  Serial.begin(115200);

  // WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.println("\nWiFi connected");

  // GM65 UART
  BarcodeSerial.begin(9600, SERIAL_8N1, GM65_RX, GM65_TX);
  Serial.println("GM65 Ready — scan barcode...");
}

void loop() {
  while (BarcodeSerial.available()) {
    char c = BarcodeSerial.read();
    lastCharTime = millis();

    if (c == '\r' || c == '\n') {
      processBarcode();
    } else {
      buffer += c;
    }
  }

  if (buffer.length() > 0 && (millis() - lastCharTime > MSG_TIMEOUT)) {
    processBarcode();
  }
}
