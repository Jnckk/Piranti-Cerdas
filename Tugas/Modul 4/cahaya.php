<?php
$servername = "localhost";
$username = "root";
$password = ""; // You missed an equal sign here
$dbname = "pirdas_modul4";

// Check if ldr_value is set in the GET request
if (isset($_GET["ldr_value"])) {
    $ldr_value = $_GET["ldr_value"];
} else {
    // Handle the case when ldr_value is not set
    echo "Error: ldr_value is not set in the GET request.";
    exit();
}

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$sql = "INSERT INTO data_cahaya (ldr_value) VALUES ('" . $ldr_value . "')";

if ($conn->query($sql) === TRUE) {
    echo "DATA LDR VALUE BERHASIL DITAMBAH";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}

$conn->close();
exit();
