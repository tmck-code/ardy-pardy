int BASE=2;
int NUM=8;

void setup() {
   for (int i=BASE; i<BASE+NUM; i++) {
     pinMode(i, OUTPUT);
   }
}

void loop() {
   for (int i=BASE; i<BASE+NUM; i++) {
     digitalWrite(i, HIGH);
     delay(100);
     digitalWrite(i, LOW);
   }
}
