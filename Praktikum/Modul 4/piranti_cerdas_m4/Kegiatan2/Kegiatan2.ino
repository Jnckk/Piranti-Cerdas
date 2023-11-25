#include <Wire.h>
#include <MPU6050_tockn.h>
#include <WiFi.h>
#include <HTTPClient.h>

MPU6050 mpu6050(Wire);

const char *SSID_WIFI = "Xiaomi";
const char *PASS_WIFI = "XiaomiChina";
const char *alamat_server = "http://192.168.100.182/piranti_cerdas_m4/save_data.php";

int16_t ax, ay, az;
int16_t gx, gy, gz;

const int ldrPin = 15;
const float threshold = 10.0;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);

  pinMode(ldrPin, INPUT);

  // Menghubungkan ke jaringan Wi-Fi
  WiFi.begin(SSID_WIFI, PASS_WIFI);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
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
    Serial.println("Sensor miring kiri");
    sendSensorData(angleX, "kiri");
  } else if (angleX < -threshold) {
    // Sumbu x < -10, sensor miring "kanan"
    Serial.println("Sensor miring kanan");
    sendSensorData(angleX, "kanan");
  } else if (angleY > threshold) {
    // Sumbu y > 10, sensor miring "depan"
    Serial.println("Sensor miring depan");
    sendSensorData(angleY, "depan");
  } else if (angleY < -threshold) {
    // Sumbu y < -10, sensor miring "belakang"
    Serial.println("Sensor miring belakang");
    sendSensorData(angleY, "belakang");
  }

  // Menampilkan nilai sensor LDR
  Serial.print("\nLDR Value: ");
  Serial.println(ldrValue);

  delay(1000); // Delay 1 detik untuk memperlambat pembacaan data
}

void sendSensorData(float angkaSumbu, String kemiringan) {
  Serial.print("Sending data to server... ");
  
  // Pastikan bahwa kemiringan tidak kosong atau null
  if (kemiringan.length() > 0) {
    HTTPClient http;
    
    // Membuat objek String untuk menyimpan URL
    String url = String(alamat_server) + "?angka_sumbu=" + String(angkaSumbu) + "&kemiringan=" + kemiringan;

    // Kirim permintaan HTTP GET
    http.begin(url);
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      Serial.println("Data berhasil terkirim");
    } else {
      Serial.println("Gagal mengirim data");
    }

    http.end();
  } else {
    Serial.println("Error: Kemiringan tidak valid");
  }
}

