#include <Arduino.h>
#line 1 "c:\\Users\\tmck0\\Documents\\dev\\ardy-pardy\\tutorials\\sketch_oct06a_traffic_lights\\sketch_oct06a_traffic_lights.ino"
int red = 10;
int yellow = 7;
int green = 4;

#line 5 "c:\\Users\\tmck0\\Documents\\dev\\ardy-pardy\\tutorials\\sketch_oct06a_traffic_lights\\sketch_oct06a_traffic_lights.ino"
void setup();
#line 11 "c:\\Users\\tmck0\\Documents\\dev\\ardy-pardy\\tutorials\\sketch_oct06a_traffic_lights\\sketch_oct06a_traffic_lights.ino"
void loop();
#line 5 "c:\\Users\\tmck0\\Documents\\dev\\ardy-pardy\\tutorials\\sketch_oct06a_traffic_lights\\sketch_oct06a_traffic_lights.ino"
void setup() {
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
}
void loop() {
  if(Serial.read()=='R') {
    digitalWrite(green, HIGH);
    delay(5000);
    digitalWrite(green, LOW);

    for(int i=0; i<3; i++) {
      delay(500);
      digitalWrite(yellow, HIGH);
      delay(500);
      digitalWrite(yellow, LOW);
    } 

    delay(500);
    digitalWrite(red, HIGH);
    delay(5000);
    digitalWrite(red, LOW);
  }
}

