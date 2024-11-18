#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(2000); // Tambahkan sedikit delay
  WiFi.mode(WIFI_STA);
  Serial.println("Alamat MAC ESP32:");
  Serial.println(WiFi.macAddress());
}

void loop() {}
