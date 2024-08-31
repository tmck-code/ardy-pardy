#include <Servo.h>

Servo myServo;

int const potPin = A0;
int potVal;
int currAngle = 0;
int angle = 0;

void setup() {
  myServo.attach(9);
  Serial.begin(9600);
}

void loop() {
  potVal = analogRead(potPin);
  currAngle = map(potVal, 0, 1023, 0, 179);
  if (currAngle != angle) {
    angle = currAngle;
    Serial.print("potVal: ");
    Serial.print(potVal);
    angle = map(potVal, 0, 1023, 0, 179);
    Serial.print(", angle: ");
    Serial.println(angle);
    myServo.write(angle);
  }
  delay(15);
}
 