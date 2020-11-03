int ledPin = 10; // define digital pin 10.

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if(Serial.read()=='R')
  {
    digitalWrite(ledPin, HIGH); // LED on
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000); // wait
    digitalWrite(ledPin, LOW); // LED off
    digitalWrite(LED_BUILTIN, LOW);
  }
}
