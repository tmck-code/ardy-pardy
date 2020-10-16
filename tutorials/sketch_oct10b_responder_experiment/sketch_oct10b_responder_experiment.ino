int led_red = 8;
int led_yellow = 7;
int led_blue = 6;

int button_r = 5;
int button_y = 4;
int button_b = 3;
int button_reset = 2;

int red;
int yellow;
int blue;

void setup() {
    Serial.begin(9600);
    pinMode(led_red, OUTPUT);
    pinMode(led_yellow, OUTPUT);
    pinMode(led_blue, OUTPUT);
    pinMode(button_r, INPUT);
    pinMode(button_y, INPUT);
    pinMode(button_b, INPUT);
    digitalWrite(led_red, LOW);
    digitalWrite(led_yellow, LOW);
    digitalWrite(led_blue, LOW);
}


// execute the code until red light is on; end cycle when reset button is pressed
void RED_YES() {
    while (digitalRead(button_reset) == 1) {
        digitalWrite(led_red, HIGH);
        digitalWrite(led_blue, LOW);
        digitalWrite(led_yellow, LOW);
    }
    clear_led();
}

// execute the code until yellow light is on; end cycle when reset button is pressed
void YELLOW_YES() {
    while (digitalRead(button_reset) == 1) {
        digitalWrite(led_red, LOW);
        digitalWrite(led_blue, LOW);
        digitalWrite(led_yellow, HIGH);
    }
    clear_led();
}

// execute the code until green light is on; end cycle when reset button ispressed
void BLUE_YES() {
    while (digitalRead(button_reset) == 1) {
        digitalWrite(led_red, LOW);
        digitalWrite(led_blue, HIGH);
        digitalWrite(led_yellow, LOW);
    }
    clear_led();
}

// all LED off
void clear_led() {
    digitalWrite(led_red, LOW);
    digitalWrite(led_blue, LOW);
    digitalWrite(led_yellow, LOW);
}


// repeatedly read pins for buttons
void loop() {
    red = digitalRead(button_r);
    yellow = digitalRead(button_y);
    blue = digitalRead(button_b);
    Serial.print("red: ");
    Serial.print(red);
    Serial.print(", yellow: ");
    Serial.print(yellow);
    Serial.print(", blue: ");
    Serial.println(blue);
    if (red == LOW)
        RED_YES(); 
    if (yellow == LOW)
        YELLOW_YES();
    if (blue == LOW)
        BLUE_YES();
}
