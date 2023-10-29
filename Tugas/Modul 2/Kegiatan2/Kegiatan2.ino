#define LED 14
#define BUZZER 12
void setup(){

  pinMode(LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
}

void loop(){
  digitalWrite(LED, HIGH);
  digitalWrite(BUZZER, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
  digitalWrite(BUZZER, LOW);
  delay(1000);
}