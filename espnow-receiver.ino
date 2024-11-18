#include <esp_now.h>
#include <WiFi.h>

// Struktur pesan yang diterima
typedef struct struct_message {
  float temperature;  // Data suhu
} struct_message;

struct_message myData;

// Callback ketika data diterima
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));

  Serial.print("Data diterima dari: ");
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.println(macStr);

  Serial.print("Suhu: ");
  Serial.print(myData.temperature);
  Serial.println(" °C");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // Inisialisasi ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Gagal menginisialisasi ESP-NOW");
    return;
  }

  // Register callback penerimaan data
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}
