#include <WiFi.h>

const char* ssid1 = "SSID1";         // Nama SSID pertama
const char* password1 = "PASSWORD";  // Password SSID pertama
const char* ssid2 = "SSID OPEN";     // Nama SSID kedua

void setup() {
  Serial.begin(9600);
  connectToWiFi();
}

void loop() {
  // Program utama dapat ditempatkan di sini
}

void connectToWiFi() {
  // Coba terhubung ke SSID pertama
  WiFi.begin(ssid1, password1);

  Serial.print("Mencoba terhubung ke " + String(ssid1) + "...");
  int attempt = 0;

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
    if (attempt >= 20) {
      break;  // Jika gagal terhubung dalam 20 detik, hentikan percobaan
    }
    attempt++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(" Terhubung ke " + String(ssid1) + "!");
  } else {
    // Jika gagal terhubung ke SSID pertama, coba terhubung ke SSID kedua
    Serial.println(" Gagal terhubung ke " + String(ssid1) + "!");
    Serial.print("Mencoba terhubung ke " + String(ssid2) + "...");

    WiFi.begin(ssid2);
    attempt = 0;

    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
      if (attempt >= 20) {
        break;  // Jika gagal terhubung dalam 20 detik, hentikan percobaan
      }
      attempt++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println(" Terhubung ke " + String(ssid2) + "!");
    } else {
      Serial.println(" Gagal terhubung ke " + String(ssid2) + "!");
    }
  }
}
