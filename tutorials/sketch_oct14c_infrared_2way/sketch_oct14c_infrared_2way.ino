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
      // irsend.sendNEC(results.value, 32);
      // delay(1000);
      // irrecv.enableIRIn(); // Start the receiver
      irrecv.resume(); // Receive the next value
  }
}
