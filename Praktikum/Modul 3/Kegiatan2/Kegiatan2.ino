#include <Wire.h>
#include <MPU6050_tockn.h>
#include <WiFi.h>

const char* ssid = "SSID";
const char* password = "PASSWORD";

MPU6050 mpu(Wire);

int16_t ax, ay, az;
int16_t gx, gy, gz;

const int buzzerPin = 15; // Pin buzzer
const float threshold = 10.0; // Ambang sudut perubahan

void setup() {
  Wire.begin();
  mpu.begin();
  mpu.calcGyroOffsets(true);
  
  pinMode(buzzerPin, OUTPUT);
  
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
  
  float angleX = atan2(gxNew, sqrt(gyNew*gyNew + gzNew*gzNew)) * 180 / PI;
  float angleY = atan2(gyNew, sqrt(gxNew*gxNew + gzNew*gzNew)) * 180 / PI;
  
  if (abs(angleX) > threshold) {
    if (angleX > 0) {
      // Sudut ke kanan
      tone(buzzerPin, 1000); // Bunyi dengan frekuensi 1000 Hz
      Serial.println("Sudut ke kanan");
    } else {
      // Sudut ke kiri
      tone(buzzerPin, 500); // Bunyi dengan frekuensi 500 Hz
      Serial.println("Sudut ke kiri");
    }
  } else if (abs(angleY) > threshold) {
    if (angleY > 0) {
      // Sudut ke belakang
      tone(buzzerPin, 800); // Bunyi dengan frekuensi 800 Hz
      Serial.println("Sudut ke belakang");
    } else {
      // Sudut ke depan
      tone(buzzerPin, 300); // Bunyi dengan frekuensi 300 Hz
      Serial.println("Sudut ke depan");
    }
  } else {
    noTone(buzzerPin); // Matikan bunyi jika tidak ada perubahan sudut
  }
  
  delay(100);
}
