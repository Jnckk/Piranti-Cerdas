<?php
$servername = "localhost"; // Ganti dengan nama server MySQL Anda
$username = "root"; // Ganti dengan username MySQL Anda
$password = ""; // Ganti dengan password MySQL Anda
$dbname = "piranti_cerdas_m4"; // Ganti dengan nama database yang telah Anda buat

// Membuat koneksi ke database
$conn = new mysqli($servername, $username, $password, $dbname);

// Memeriksa koneksi
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Mendapatkan data dari Arduino
$angka_sumbu = $_GET['angka_sumbu'];
$kemiringan = $_GET['kemiringan'];

// Menyimpan data ke tabel database
$sql = "INSERT INTO data_sensor (angka_sumbu, kemiringan) VALUES ($angka_sumbu, '$kemiringan')";

if ($conn->query($sql) === TRUE) {
    echo "Data berhasil disimpan";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

// Menutup koneksi
$conn->close();
