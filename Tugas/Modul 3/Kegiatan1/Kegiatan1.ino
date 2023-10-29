#include <WiFi.h>

const char *ssid = "asukon";        // Nama SSID Wi-Fi
const char *password = "cokjaran";  // Kata sandi Wi-Fi

void setup() {
  Serial.begin(9600);

  // Menghubungkan ESP32 ke jaringan Wi-Fi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Menghubungkan ke Wi-Fi...");
  }

  Serial.println("Terhubung ke Wi-Fi");
}

void loop() {
  // Kode program Anda dapat diletakkan di sini
}
