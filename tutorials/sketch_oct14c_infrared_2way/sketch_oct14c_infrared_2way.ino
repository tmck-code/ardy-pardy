#include<IRremote.h>

int RECV_PIN=11;
IRrecv irrecv(RECV_PIN);
decode_results results;
IRsend irsend;

void setup() {
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
      Serial.println("Received: " + String(results.value, HEX));
      digitalWrite(LED_BUILTIN, HIGH);
      delay(2000);
      irsend.sendNEC(results.value, 32);
      Serial.println("Sent: " + String(results.value, HEX));
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
      irrecv.enableIRIn(); // Start the receiver
      irrecv.resume(); // Receive the next value
  }
}
