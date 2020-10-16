#include<IRremote.h>

#define RECV_PIN 11

IRrecv irrecv(RECV_PIN);
decode_results results;
IRsend irsend;

const unsigned long LG_VOL_UP = 0x5EA158A7;
const unsigned long LG_VOL_DOWN = 0xD5EA1D827;
const unsigned long LG_BUTTONUP = 0xFFFFFFFF;
long lastOp = 0x0;
long found = 0x0;

unsigned long findOp(long value) {
  switch(value) {
    case(0xff20df): return LG_VOL_DOWN; // BRT_DOWN
    case(0xffa05f): return LG_VOL_UP; // BRT_UP
    default:        return 0x0;
  }
}

void setup() {
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value == 0xffffffff) {
      found = lastOp;
    } else {
      found = findOp(results.value);
    }
    Serial.println(String(results.value, HEX) + " -> " + String(found, HEX));
    if (found != 0x0) {
      irsend.sendNEC(found, 32);
      irsend.sendNEC(LG_BUTTONUP, 32);
      irrecv.enableIRIn(); // Start the receiver
      lastOp = found;
    }
    irrecv.resume(); // Receive the next value
  }
}
