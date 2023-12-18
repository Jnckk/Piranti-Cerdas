#include <Wire.h>
#include <MPU6050_tockn.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Xiaomi";
const char* password = "XiaomiChina";

MPU6050 mpu(Wire);

int16_t ax, ay, az;
int16_t gx, gy, gz;

const int buzzerPin = 15; // Buzzer Pin
const int ledPin = 2;    // LED Pin
const float threshold = 5.0; // Threshold angle change

const char* serverUrl = "http://192.168.100.182/piranti_cerdas_M6/insert_data.php"; // Replace with your server address

void setup() {
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets(true);

  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  mpu.update();

  int16_t gxNew = mpu.getGyroX();
  int16_t gyNew = mpu.getGyroY();
  int16_t gzNew = mpu.getGyroZ();

  float angleX = atan2(gxNew, sqrt(gyNew * gyNew + gzNew * gzNew)) * 180 / PI;
  float angleY = atan2(gyNew, sqrt(gxNew * gxNew + gzNew * gzNew)) * 180 / PI;

  if (abs(angleX) > threshold || abs(angleY) > threshold) {
    // MPU6050 not on a flat surface
    sendData(angleX, angleY, "Tidak pada bidang datar");
    tone(buzzerPin, 2000);
    digitalWrite(ledPin, LOW);
    Serial.println("MPU6050 tidak pada bidang datar");
  } else {
    // MPU6050 on a flat surface
    sendData(angleX, angleY, "Pada bidang datar");
    noTone(buzzerPin);
    digitalWrite(ledPin, HIGH);
    Serial.println("MPU6050 pada bidang datar");
  }

  delay(1000);
}

void sendData(float angleX, float angleY, const char* status) {
  HTTPClient http;
  http.begin(serverUrl);

  String data = "angleX=" + String(angleX) + "&angleY=" + String(angleY) + "&status=" + String(status);

  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpResponseCode = http.POST(data);

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.println("Error on HTTP request");
  }

  http.end();
}