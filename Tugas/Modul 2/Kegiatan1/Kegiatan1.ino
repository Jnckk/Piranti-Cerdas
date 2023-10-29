#define LIGHT_SENSOR_PIN 32 //

void setup(){
  Serial.begin(9600);
}

void loop(){

  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  Serial.print("Analog Value = ");
  Serial.print(analogValue);
  Serial.println("");

  delay(500);
}
