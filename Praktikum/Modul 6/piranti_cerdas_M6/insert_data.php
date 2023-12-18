<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "smart_home";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$angleX = isset($_POST["angleX"]) ? $_POST["angleX"] : null;
$angleY = isset($_POST["angleY"]) ? $_POST["angleY"] : null;
$status = isset($_POST["status"]) ? $_POST["status"] : null;

// Insert new data
$sqlInsert = "INSERT INTO sensor_data (angleX, angleY, status) VALUES ('$angleX', '$angleY', '$status')";
$conn->query($sqlInsert);

// Check the total number of entries
$sqlCount = "SELECT COUNT(*) AS total FROM sensor_data";
$result = $conn->query($sqlCount);

if ($result->num_rows > 0) {
    $row = $result->fetch_assoc();
    $totalEntries = $row["total"];

    // If the total number of entries exceeds 100, delete the oldest entries
    if ($totalEntries > 100) {
        $deleteCount = $totalEntries - 100;
        $sqlDelete = "DELETE FROM sensor_data ORDER BY timestamp ASC LIMIT $deleteCount";
        $conn->query($sqlDelete);
    }
}

$conn->close();
?>