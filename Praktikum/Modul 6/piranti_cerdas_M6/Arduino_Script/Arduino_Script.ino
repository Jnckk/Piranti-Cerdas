#include <Wire.h>
#include <MPU6050_tockn.h>
#include <WiFi.h>

const char* ssid = "Xiaomi";
const char* password = "XiaomiChina";

MPU6050 mpu(Wire);

int16_t ax, ay, az;
int16_t gx, gy, gz;

const int buzzerPin = 15; // Pin buzzer
const int ledPin = 2;    // Pin LED
const float threshold = 10.0; // Ambang sudut perubahan

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
  
  float angleX = atan2(gxNew, sqrt(gyNew*gyNew + gzNew*gzNew)) * 180 / PI;
  float angleY = atan2(gyNew, sqrt(gxNew*gxNew + gzNew*gzNew)) * 180 / PI;
  
  if (abs(angleX) > threshold || abs(angleY) > threshold) {
    // MPU6050 tidak pada bidang datar
    tone(buzzerPin, 2000); // Bunyi dengan frekuensi 2000 Hz (suara kencang)
    digitalWrite(ledPin, LOW); // Matikan LED
    Serial.println("MPU6050 tidak pada bidang datar");
  } else {
    // MPU6050 pada bidang datar
    noTone(buzzerPin); // Matikan bunyi
    digitalWrite(ledPin, HIGH); // Nyalakan LED
    Serial.println("MPU6050 pada bidang datar");
  }
  
  delay(100);
}
