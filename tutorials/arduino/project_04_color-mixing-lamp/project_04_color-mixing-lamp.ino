const int greenPin = 9;
const int redPin = 11;
const int bluePin = 10;

const int redSensorPin = A2;
const int greenSensorPin = A1;
const int blueSensorPin = A0;

int redValue = 0;
int greenValue = 0;
int blueValue = 0;

int redSensorValue = 0;
int greenSensorValue = 0;
int blueSensorValue = 0;


void setup() {
  Serial.begin(9600);

  pinMode(greenPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}


void loop() {
  redSensorValue = analogRead(redSensorPin);
  delay(5);
  greenSensorValue = analogRead(greenSensorPin);
  delay(5);
  blueSensorValue = analogRead(blueSensorPin);

  Serial.print("Raw sensor values:\t red:");
  Serial.print(redSensorValue);
  Serial.print("\t green:");
  Serial.print(greenSensorValue);
  Serial.print("\t blue:");
  Serial.print(blueSensorValue);

  redValue = ((redSensorValue/4)/10)*10;
  greenValue = ((greenSensorValue/4)/10)*10;
  blueValue = ((blueSensorValue/4)/10)*10;

  Serial.print(", Mapped sensor values:\t red:");
  Serial.print(redValue);
  Serial.print("\t green:");
  Serial.print(greenValue);
  Serial.print("\t blue:");
  Serial.println(blueValue);

  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);

  // delay(50);
}