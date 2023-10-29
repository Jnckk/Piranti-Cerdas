const int sensorPin = 13;  // Pin untuk sensor cahaya (input analog)
const int redLED = 12;    // Pin untuk LED merah (output digital)
const int greenLED = 14;  // Pin untuk LED hijau (output digital)
const int yellowLED = 27;   // Pin untuk LED biru (output digital)

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // Baca nilai analog dari sensor cahaya
  int lightValue = analogRead(sensorPin);

  // Tampilkan nilai intensitas cahaya pada serial monitor
  Serial.print("Intensitas Cahaya: ");
  Serial.println(lightValue);

  // Tentukan kondisi berdasarkan nilai intensitas cahaya
  if (lightValue < 500) {
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    Serial.println("Cahaya Gelap");
  } else if (lightValue >= 500 && lightValue < 1000) {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    Serial.println("Cahaya Redup");
  } else {
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    Serial.println("Cahaya Terang");
  }

  delay(1000);  // Delay 1 detik sebelum membaca ulang nilai sensor
}
