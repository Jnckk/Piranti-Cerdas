#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPL65idlpZTT"
#define BLYNK_TEMPLATE_NAME "Praktikum"
#define BLYNK_AUTH_TOKEN "H9K9Q-q8THCuHlojeFT1r__kJUjcugHX"
#define LIGHT_SENSOR_PIN 32
#define RELAY_PIN 5

BlynkTimer timer;

// Konfigurasi nama hotspot/SSID beserta password
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Test";
char pass[] = "TestEsp32";

bool manualControl = false; // Flag untuk kontrol manual

void send_data() {
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  Serial.print("Analog Value = ");
  Serial.println(analogValue);

  // Kirim nilai keadaan cahaya ke Blynk
  Blynk.virtualWrite(V0, analogValue);

  // Berdasarkan nilai cahaya, tentukan keadaan dan kirim ke Blynk
  if (analogValue < 500) {
    Blynk.virtualWrite(V2, "Gelap"); // Status cahaya

    // Jika kontrol manual tidak aktif, nyalakan lampu secara otomatis
    if (!manualControl) {
      digitalWrite(RELAY_PIN, HIGH); // Nyalakan lampu
      Blynk.virtualWrite(V1, HIGH); // Update tombol Blynk menjadi ON
    }
  } else {
    Blynk.virtualWrite(V2, "Terang"); // Status cahaya

    // Jika kontrol manual tidak aktif, matikan lampu secara otomatis
    if (!manualControl) {
      digitalWrite(RELAY_PIN, LOW); // Matikan lampu
      Blynk.virtualWrite(V1, LOW); // Update tombol Blynk menjadi OFF
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, send_data);
}

void loop() {
  Blynk.run();
  timer.run();
}

// Fungsi dipanggil saat tombol on/off di Blynk ditekan
BLYNK_WRITE(V1) {
  int relayState = param.asInt();

  if (manualControl) {
    digitalWrite(RELAY_PIN, relayState);
  }
}

// Fungsi dipanggil saat tombol kontrol manual diaktifkan atau dinonaktifkan
BLYNK_WRITE(V3) {
  manualControl = param.asInt();
  if (!manualControl) {
    // Jika kontrol manual dinonaktifkan, sesuaikan relay berdasarkan kondisi cahaya
    send_data();
  }
}
