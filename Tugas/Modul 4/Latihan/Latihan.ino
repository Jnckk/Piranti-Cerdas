#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>

#define SENSORPIN 34
#define LEDPIN 25

const char* ssid = "kost belakang";
const char* password = "OKTOPUS8";
const char* serverName = "http://172.20.10.6/pirdas_modul4/cahaya.php";

void setup() {
  Serial.begin(9600);
  pinMode(LEDPIN, OUTPUT);
  delay(1000);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  String wifiName = WiFi.SSID();
  String localwifiIP = WiFi.localIP().toString();
  Serial.println();
  Serial.println("Connected to " + wifiName);
  Serial.println("Local IP WIFI: " + localwifiIP);
}

void loop() {
  int ldr_value = analogRead(SENSORPIN);

  if (ldr_value > 100) {
    Serial.println("Cahaya Terang ");
    digitalWrite(LEDPIN, LOW);
    Serial.print("Intensitas Cahaya: ");
    Serial.print(ldr_value);
    Serial.println();
  } else {
    Serial.println("Cahaya Gelap ");
    digitalWrite(LEDPIN, HIGH);
    Serial.print("Intensitas Cahaya: ");
    Serial.print(ldr_value);
    Serial.println();
  }

  delay(1000);

  String url = serverName;
  url += "?ldr_value=";
  url += String(ldr_value);

  HTTPClient http;
  http.begin(url);

  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    Serial.println("Data sent successfully!");
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();
  delay(10000); // Add a closing parenthesis here
}
