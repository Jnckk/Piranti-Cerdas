#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
#define BLYNK_TEMPLATE_ID "TMPL6mFGVAlSv"
#define BLYNK_TEMPLATE_NAME "Latihan Praktikum Modul 5"
#define BLYNK_AUTH_TOKEN "tZ9Z5YAL8WFHVlNMf5EbFC08klNptbjb"
#define DHT_PIN 4
#define BUZZER_PIN 5

BlynkTimer timer;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "SSID";
char pass[] = "PASSWORD";

DHT dht(DHT_PIN, DHT11);

void send_data() {
  float temperature = dht.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(temperature);

  String suhu_keterangan;

  if (temperature > 30.0) {
    suhu_keterangan = "Panas";
    Serial.println("Status: Panas");
    tone(BUZZER_PIN, 1000, 500); // 1000 Hz for 500 milliseconds
  } else if (temperature > 25.0) {
    suhu_keterangan = "Hangat";
    Serial.println("Status: Hangat");
    tone(BUZZER_PIN, 500, 200); // 500 Hz for 200 milliseconds
  } else {
    suhu_keterangan = "Normal";
    Serial.println("Status: Normal");
    noTone(BUZZER_PIN);
  }

  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, suhu_keterangan);
}



void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  dht.begin();
  
  pinMode(BUZZER_PIN, OUTPUT);

  timer.setInterval(1000L, send_data);
}

void loop() {
  Blynk.run();
  timer.run();
}
