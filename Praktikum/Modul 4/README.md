## Setup
Pindahkan folder "piranti_cerdas_m4" ke dalam folder htdocs yang ada di dalam folder xampp.

Code SQL untuk mmembuat database dan tabel pada localhost/phpmyadmin
```bash
CREATE DATABASE IF NOT EXISTS piranti_cerdas_m4;
USE piranti_cerdas_m4;

CREATE TABLE IF NOT EXISTS data_sensor (
   id_sensor_gerak INT AUTO_INCREMENT PRIMARY KEY,
   angka_sumbu FLOAT,
   kemiringan ENUM('kanan', 'kiri', 'depan', 'belakang')
);

```

## Rangkaian

Sensor LDR

```bash
  - Kaki yang pendek (GND): Terhubung ke jalur negatif (-) pada breadboard menggunakan resistor
  - Kaki yang panjang (VCC): Terhubung ke jalur positif (+) pada breadboard
  - antara resistor dan kaki pendek (GND) hubungkan ke pin 15 pada ESP32
```

MPU6050

```bash
  - VCC: Terhubung ke jalur positif (+) pada breadboard
  - GND: Terhubung ke jalur negatif (-) pada breadboard
  - SDA: Terhubung ke pin D21 pada NodeMCU ESP32
  - SCL: Terhubung ke pin D22 pada NodeMCU ESP32
```