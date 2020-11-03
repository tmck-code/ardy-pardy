# 1 "c:\\Users\\tmck0\\Documents\\dev\\ardy-pardy\\tutorials\\sketch_oct06a_traffic_lights\\sketch_oct06a_traffic_lights.ino"
int red = 10;
int yellow = 7;
int green = 4;

void setup() {
  Serial.begin(9600);
  pinMode(red, 0x1);
  pinMode(yellow, 0x1);
  pinMode(green, 0x1);
}
void loop() {
  if(Serial.read()=='R') {
    digitalWrite(green, 0x1);
    delay(5000);
    digitalWrite(green, 0x0);

    for(int i=0; i<3; i++) {
      delay(500);
      digitalWrite(yellow, 0x1);
      delay(500);
      digitalWrite(yellow, 0x0);
    }

    delay(500);
    digitalWrite(red, 0x1);
    delay(5000);
    digitalWrite(red, 0x0);
  }
}
