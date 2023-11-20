int LDR_Val = 0;
int SENSOR = 34;
int LED = 25;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  LDR_Val = analogRead(SENSOR);
  Serial.print("LDR Output: ");
  Serial.println(LDR_Val);

  if (LDR_Val > 100) {
    Serial.println("Cahaya Terang");
    digitalWrite(LED, LOW); // Assuming LOW turns the LED on
  } else {
    Serial.println("Cahaya Gelap");
    digitalWrite(LED, HIGH); // Assuming HIGH turns the LED off
  }

  delay(1000);
}
