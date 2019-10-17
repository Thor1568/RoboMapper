#include <dht.h>
//Temperature sensor reader

dht DHT;

const int dhtPin = 22;
const int WAIT = 500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial init");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
  delay(WAIT);
}
