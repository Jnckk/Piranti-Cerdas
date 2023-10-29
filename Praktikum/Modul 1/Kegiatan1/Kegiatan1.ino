const int switchPin = 21;  // Pin yang terhubung ke switch
const int ledPin = 5;      // Pin yang terhubung ke LED
int switchState = 0;       // Menyimpan status switch (0 atau 1)

void setup() {
  Serial.begin(9600);
  pinMode(switchPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  switchState = digitalRead(switchPin);  // Membaca status switch

  if (switchState == HIGH) {     // Jika switch ditekan (HIGH)
    digitalWrite(ledPin, HIGH);  // Nyalakan LED
    delay(1000);
    digitalWrite(ledPin, LOW);  // Matikan LED
  } else {
    digitalWrite(ledPin, LOW);  // Matikan LED
  }

  delay(200);
}