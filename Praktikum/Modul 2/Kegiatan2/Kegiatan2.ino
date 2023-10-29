const int sensorPin = 32;  // Pin untuk sensor cahaya (input digital)
const int buzzerPin = 26;  // Pin untuk buzzer (output digital)

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Baca nilai digital dari sensor cahaya
  int lightValue = digitalRead(sensorPin);

  // Jika sensor mendeteksi gelap (nilai LOW), aktifkan buzzer dan tampilkan "Gelap" pada Serial Monitor
  if (lightValue == LOW) {
    digitalWrite(buzzerPin, HIGH);
    Serial.println("Gelap");
  } else {
    // Jika sensor mendeteksi terang (nilai HIGH), matikan buzzer dan tampilkan "Terang" pada Serial Monitor
    digitalWrite(buzzerPin, LOW);
    Serial.println("Terang");
  }

  delay(1000);  // Delay 1 detik sebelum membaca ulang nilai sensor
}
