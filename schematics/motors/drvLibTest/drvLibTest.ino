#include <DRVDriver.h>

const int in1 = 2;
const int in2 = 3;
const int in3 = 4;
const int in4 = 5;
const int pwmSpeed = 180;
const int d = 500;

DRVDriver frontMotor = DRVDriver(in1, in2, in3, in4, pwmSpeed);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial init");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  frontMotor.forward(pwmSpeed);
  delay(d);
  frontMotor.backward(pwmSpeed);
  delay(d);
  Serial.println("1d motions done");
  delay(d);
  frontMotor.left(pwmSpeed, false);
  delay(d);
  frontMotor.left(pwmSpeed, true);
  delay(d);
  Serial.println("2nd motions done");
  frontMotor.brake();
  delay(10000);
}
