#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define BLYNK_TEMPLATE_ID "TMPL6dFJNSMqX"
#define BLYNK_TEMPLATE_NAME "Latihan Praktikum"
#define BLYNK_AUTH_TOKEN "Bairo_PL0snzws3bG3Bz5PCNlNVykLrg"
#define LIGHT_SENSOR_PIN 32

BlynkTimer timer;

// Konfigurasi nama hotspot/SSID beserta password
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Xiaomi";
char pass[] = "XiaomiChina";

void send_data() {
  delay(1000);
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  Serial.println("Analog Value = ");
  Serial.println(analogValue);
  Blynk.virtualWrite(V0, analogValue);
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(1000L, send_data);
}

void loop() {
  Blynk.run();
  timer.run();
}
