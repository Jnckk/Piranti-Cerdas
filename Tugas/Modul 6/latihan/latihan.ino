#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#define BLYNK_TEMPLATE_ID "TMPL6mFGVAlSv"
#define BLYNK_TEMPLATE_NAME "Latihan Praktikum Modul 5"
#define BLYNK_AUTH_TOKEN "tZ9Z5YAL8WFHVlNMf5EbFC08klNptbjb"
#define DHT_PIN 4       // Pin koneksi sensor DHT
#define BUZZER_PIN 5    // Pin koneksi Buzzer

BlynkTimer timer;

// Konfigurasi nama hotspot/SSID beserta password
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "SSID WIFI";
char pass[] = "PASSWORD";

DHT dht(DHT_PIN, DHT11);

void send_data() {
  float temperature = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(temperature);

  // Keterangan suhu
  String suhu_keterangan;

  if (temperature > 30.0) {
    suhu_keterangan = "Panas";
    // Suhu panas, bunyikan Buzzer dengan frekuensi tinggi
    tone(BUZZER_PIN, 1000, 500); // 1000 Hz for 500 milliseconds
  } else if (temperature > 25.0) {
    suhu_keterangan = "Hangat";
    // Suhu hangat, bunyikan Buzzer dengan frekuensi sedang
    tone(BUZZER_PIN, 500, 200); // 500 Hz for 200 milliseconds
  } else {
    suhu_keterangan = "Normal";
    // Suhu normal, matikan Buzzer
    noTone(BUZZER_PIN);
  }

  // Mengirim suhu dan keterangan ke Blynk
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, suhu_keterangan);
}


void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  dht.begin();
  
  // Mengatur pin Buzzer sebagai OUTPUT
  pinMode(BUZZER_PIN, OUTPUT);

  // Menjadwalkan fungsi send_data setiap 1000ms (1 detik)
  timer.setInterval(1000L, send_data);
}

void loop() {
  Blynk.run();
  timer.run();
}
