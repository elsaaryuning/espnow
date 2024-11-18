#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0xC0, 0x5D, 0x89, 0xB1, 0x62, 0xBC};
typedef struct struct_message {
  float temperature;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nStatus Pengiriman: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Berhasil" : "Gagal");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Gagal menginisialisasi ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  // Menyalin alamat MAC penerima ke struktur peerInfo
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Gagal menambahkan peer");
    return;
  }
}

void loop() {
  myData.temperature = random(200, 400) / 10.0;
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  if (result == ESP_OK) {
    Serial.print("Data suhu yang dikirim: ");
    Serial.println(myData.temperature);
  } else {
    Serial.println("Gagal mengirim data");
  }

  delay(2000);
}
