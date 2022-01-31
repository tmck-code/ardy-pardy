#include <DHT.h>
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
  
void setup(){
  Serial.begin(9600);
  dht.begin();
}
  
void loop(){
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  Serial.println("DHT11\tTemp: " + String(t) + "C, Humidity: " + String(h) + "%");
  delay(1000);
}
