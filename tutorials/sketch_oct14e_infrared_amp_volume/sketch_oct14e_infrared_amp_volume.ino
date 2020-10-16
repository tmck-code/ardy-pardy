#include <IRremote.h>

IRsend irsend;
const unsigned long LG_VOL_UP = 0x5EA158A7;
const unsigned long LG_VOL_DOWN = 0xD5EA1D827;
const unsigned long LG_BUTTONUP = 0xFFFFFFFF;
String msg;
double choice;
double current = -40.00;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void adjust_volume(long sig, int n) {
  for (int i=0; i<n; i++){
    irsend.sendNEC(sig, 32);
    irsend.sendNEC(LG_BUTTONUP, 32);
  }
}

void volume_down(int n) {
  adjust_volume(LG_VOL_DOWN, n);
}

void volume_up(int n) {
  adjust_volume(LG_VOL_UP, n);
}

void loop() {
  while (Serial.available()) {
    if (Serial.available() > 0) {
      delay(3);
      char c = Serial.read();  //gets one byte from serial buffer
      msg += c; //makes the string readString
    }
  }
  choice = msg.toFloat();
  if (choice < 0) {
    digitalWrite(LED_BUILTIN, HIGH);
    double diff = choice - current;
    Serial.println("Choice: " + String(choice));
    if (diff > 0) {
      volume_up(diff*2);
    } else if (diff < 0) {
      volume_down(abs(diff*2));
    } else {
      Serial.println("volume is already set");
    }
    current = choice;
    msg = "";
    choice = 0;
    digitalWrite(LED_BUILTIN, LOW);
  }
}
