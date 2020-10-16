#include<IRremote.h>

#define RECV_PIN 11

IRrecv irrecv(RECV_PIN);
decode_results results;
IRsend irsend;

char* findOp(int value) {
  switch(value) {
    case(0xffe01f): return "ON";
    case(0xff609f): return "OFF";
    case(0xffb04f): return "RED";
    case(0xffa857): return "ORANGE1";
    case(0xff9867): return "ORANGE2";
    case(0xff8877): return "YELLOW";
    case(0xff30cf): return "GREEN";
    case(0xff28d7): return "BLUE1";
    case(0xff18e7): return "BLUE2";
    case(0xff08f7): return "BLUE3";
    case(0xff708f): return "BLUE4";
    case(0xff6897): return "INDIGO";
    case(0xff58a7): return "PURPLE";
    case(0xff48b7): return "PINK";
    case(0xffd02f): return "WHITE";
    case(0xffa05f): return "BRT_UP";
    case(0xff20df): return "BRT_DOWN";
    case(0xfff00f): return "FLASH";
    case(0xffe817): return "STROBE";
    case(0xffd827): return "FADE";
    case(0xffc837): return "SMOOTH";
    case(0xff906f): return "R";
    case(0xff10ef): return "G";
    case(0xff50af): return "B";
    default:        return "?";
  }
}

void setup() {
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value != 0xffffffff) {
      Serial.println(String(results.value, HEX) + " -> " + findOp(results.value));
      // irsend.sendNEC(results.value, 32);
      // Serial.println("Sent: " + String(results.value, HEX));
    }
    // irrecv.enableIRIn(); // Start the receiver
    irrecv.resume(); // Receive the next value
  }
}
