const int sensorPin = A0;
float baselineTemp = 20.0;

float readTemp(int pinNumber) {
  int adc = analogRead(pinNumber);
  Serial.print("Sensor Value: ");
  Serial.print(adc);

  float voltage = (adc/1024.0) * 5.0;
  Serial.print(", Volts: ");
  Serial.print(voltage);

  float temp = (voltage - .5) * 100;
  Serial.print(", degrees C: ");
  Serial.println(temp);

  return temp;
}

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  for (int pinNumber = 2; pinNumber < 5; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, HIGH);
    delay(100);
    digitalWrite(pinNumber, LOW);
  }

  baselineTemp = readTemp(sensorPin);
  Serial.print("baseline temp is: ");
  Serial.println(baselineTemp);
}

void loop() {
  float temperature = readTemp(sensorPin);

  if (temperature >= (baselineTemp+2)) {
    // if the temperature is at or above 22 degrees C, turn on the third LED:
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  } else if (temperature >= (baselineTemp+1)) {
    // if the temperature is at or above 21 degrees C, turn on the second LED:
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } else if (temperature >= baselineTemp) {
    // if the temperature is at baseline, turn on the first LED:
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else {
    // if the current temperature is lower than the baseline, turn off all LEDs:
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  }
  delay(10); // delay in between reads for stability
}
