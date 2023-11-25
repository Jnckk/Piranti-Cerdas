#include <Wire.h>
#include <MPU6050_tockn.h>

MPU6050 mpu6050(Wire);

const int ldrPin = 15;
const float threshold = 10.0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  pinMode(ldrPin, INPUT);
}

void loop() {
  mpu6050.update();

  int16_t gxNew = mpu6050.getGyroX();
  int16_t gyNew = mpu6050.getGyroY();
  int16_t gzNew = mpu6050.getGyroZ();

  float angleX = atan2(gxNew, sqrt(gyNew * gyNew + gzNew * gzNew)) * 180 / PI;
  float angleY = atan2(gyNew, sqrt(gxNew * gxNew + gzNew * gzNew)) * 180 / PI;

  int ldrValue = analogRead(ldrPin);

  // Kondisi untuk sensor LDR
  if (ldrValue >= 0 && ldrValue <= 50) {
    Serial.println("Keadaan gelap");
  } else if (ldrValue > 50 && ldrValue <= 500) {
    Serial.println("Keadaan redup");
  } else if (ldrValue > 500 && ldrValue <= 2000) {
    Serial.println("Cahaya terang");
  } else {
    Serial.println("Sangat terang");
  }

  // Kondisi untuk sensor MPU6050
  if (angleX > threshold) {
    // Sumbu x > 10, sensor miring "kiri"
    Serial.print("Sensor miring kiri | ");
  } else if (angleX < -threshold) {
    // Sumbu x < -10, sensor miring "kanan"
    Serial.print("Sensor miring kanan | ");
  } else if (angleY > threshold) {
    // Sumbu y > 10, sensor miring "depan"
    Serial.print("Sensor miring depan | ");
  } else if (angleY < -threshold) {
    // Sumbu y < -10, sensor miring "belakang"
    Serial.print("Sensor miring belakang | ");
  }

  // Menampilkan nilai sensor LDR
  Serial.print("\nLDR Value: ");
  Serial.println(ldrValue);

  delay(1000); // Delay 1 detik untuk memperlambat pembacaan data
}
