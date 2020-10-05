void setup()
{
  // set the baud rate at 9600 to match the software set up. When connected to a specific device, 
  //(e.g. bluetooth), the baud rate needs to be the same with it.
  Serial.begin(9600);
    // initialize digital pin 13 as output. When using I/O ports on an Arduino, this kind of set up is always needed.
  pinMode(13,OUTPUT);
}
void loop()
{
  // read the instruction or character from PC to Arduino
  if(Serial.read()=='R')
  {
    digitalWrite(13,HIGH);
    delay(500);
    Serial.println("Hello World!");
  }
}
