#include <LMotorDriver.h>
const int in1 = 8;
const int in2 = 9;
const int ena = 10;
const int in3 = 7;
const int in4 = 6;
const int enb = 5;
const int s = 200;
const int w = 2000;

LMotorDriver d = LMotorDriver(in1, in2, in3, in4, ena, enb);

//As of right now, forward turns right and backward turns left. turns go straight
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial start ----------------");
  d.setSpd(s);
  /*
  d.left(s, true);
  d.right(s, true);
  delay(w);
  d.left(s, false);
  d.right(s, false);
  delay(w);
  d.brake();
  delay(w*5);
  */
}

void mForward() {
  d.forward();
  delay(w);
  d.brake();
  delay(400);  
}

void mBackward() {
  d.backward();
  delay(w);
  d.brake();
  delay(400);    
}

void mLeft90() {
  d.left(true);
  delay(400);
  d.brake();  
  delay(400);
}

void mLeft45() {
  d.left(true);
  delay(200);
  d.brake();  
  delay(400);
} 


void mRight90() {
  d.right(true);
  delay(400);
  d.brake(); 
  delay(400); 
}

void mRight45() {
  d.right(true);
  delay(200);
  d.brake(); 
  delay(400); 
} 

void loop() {
  // put your main code here, to run repeatedly:
 //
  mForward();
  mLeft90();
  mForward();
  mRight90();
  mBackward();
  mRight90();
  mForward();
  mLeft90();
  delay(w);
  mLeft90();
  mLeft90();
  mLeft90();
  mLeft90();
  delay(500);
  mRight90();
  mRight90();
  mRight90();
  mRight90();
  delay(w);
}
