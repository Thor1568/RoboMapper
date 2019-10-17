#include <Ultrasonic.h>
//make object for ULT sensor in future, for now
const int u1_trig = 11;
const int u1_echo = 12;

Ultrasonic u1 = Ultrasonic(u1_echo, u1_trig);
/*
  distance = (traveltime/2) x speed of sound

  The speed of sound is: 343m/s = 0.0343 cm/uS = 1/29.1 cm/uS

  Or in inches: 13503.9in/s = 0.0135in/uS = 1/74in/uS

  I can also use the NewPing library and make a sonar object
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial init");
}

long duration() {
  digitalWrite(u1_trig, LOW);
  delayMicroseconds(5);
  digitalWrite(u1_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(u1_trig, LOW);
  double dur = pulseIn(u1_echo, HIGH);
  double inches = (dur / 2.0) / 74.0;
  return inches;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Dist: ");
  Serial.print(u1.readCenti());
  Serial.println("--------------");
  delay(1000);
}
