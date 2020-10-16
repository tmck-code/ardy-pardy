int redpin = 11; //select the pin for the red LED
int bluepin =10;// select the pin for the blue LED
int greenpin =9; // select the pin for the green LED
int val;

void setup() {
    pinMode(redpin, OUTPUT);
    pinMode(bluepin, OUTPUT);
    pinMode(greenpin, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    if(Serial.read()=='R') {
        for(val=255; val>0; val-=5) {
            analogWrite(11, val);
            analogWrite(10, 255-val);
            analogWrite(9, 128-val);
            delay(25);
        }
        Serial.println(val, DEC);
        digitalWrite(11, LOW);
        digitalWrite(10, LOW);
        digitalWrite(9, LOW);
    }
}
