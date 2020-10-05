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
    delay(1000); // wait
  }
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.

}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}