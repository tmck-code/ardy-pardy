int ledpin=11;
int inpin=7;
int val;

void setup() {
  pinMode(ledpin,OUTPUT);
  pinMode(inpin,INPUT);
}

void loop(){
  // read the level value of pin 7 and assign if to val
  val=digitalRead(inpin);
  // check if the button is pressed, if yes, turn on the LED
  if(val==LOW) {
    digitalWrite(ledpin,HIGH);
    digitalWrite(LED_BUILTIN,HIGH);
  } else {
    digitalWrite(ledpin,LOW);
    digitalWrite(LED_BUILTIN,LOW);
  }
}
