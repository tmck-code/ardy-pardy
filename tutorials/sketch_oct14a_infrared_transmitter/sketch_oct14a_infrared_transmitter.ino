#include <IRremote.h>

int led = 3;
IRsend irsend;
const unsigned long LG_VOL_UP = 0x5EA158A7;
const unsigned long LG_VOL_DOWN = 0xD5EA1D827;
const unsigned long LG_POWER = 0x20DF10EF;
const unsigned long LG_BUTTONUP = 0xFFFFFFFF;
long sig = 0x0;
char *choice;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  choice = Serial.read();
  if(choice=='U') {
    sig = LG_VOL_UP;
    Serial.println("Chose LG_VOL_UP");
  } else if(choice=='D') {
    sig = LG_VOL_DOWN;
    Serial.println("Chose LG_VOL_DOWN");
  } else {
    sig = 0x0;
  }
  if (sig != 0x0) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(String("sending code: ") + String(sig, HEX));
    for (int i=0; i<5; i++) {
      irsend.sendNEC(sig, 32);
      irsend.sendNEC(LG_BUTTONUP, 32);
    }
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);
  }
}
