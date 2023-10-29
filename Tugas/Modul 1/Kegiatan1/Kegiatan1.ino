#define LED_BUILTIN 2 //led buiildin ESP32 in pin2
// the setup function runs once when you press reset or power the board
void setup(){
pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
digitalWrite(LED_BUILTIN, HIGH);
delay(1000);
digitalWrite(LED_BUILTIN, LOW);
delay(1000);
}