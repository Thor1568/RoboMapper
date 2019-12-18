#include <Ultrasonic.h>
#include <DRVDriver.h>
#include <dht.h>
#include <Wire.h>

//constants
int frontDist = 0, backDist = 0, leftDist= 0, rightDist =0;
int wet = 0;
int temp = 75, humidity= 20, robotAngle= 90, controlMode= 1;
//motor control pins
const int m1_in1, m1_in2;
const int m2_in1, m2_in2;
int motorSpeed = 100;

//sensors
const int front_echo, front_trig, rear_echo, rear_trig, left_echo, left_trig, right_echo, right_trig; 
const int dhtPin;
const int waterPin;
//objects
Ultrasonic front = Ultrasonic(front_echo, front_trig);
Ultrasonic rear = Ultrasonic(rear_echo, rear_trig);
Ultrasonic left = Ultrasonic(left_echo, left_trig);
Ultrasonic right = Ultrasonic(right_echo, right_trig);
DRVDriver driveTrain = DRVDriver(m1_in1, m1_in2, m2_in1, m2_in2, motorSpeed);

void setup() {
    //move this too b
    Serial.begin(9600);
}

void sendDataSerial(int frontDist, int backDist, int leftDist, int rightDist, int humidity, int temp, int wet, int robotAngle, int controlMode) {
  Serial.print("0 ");
  Serial.print(frontDist);
  Serial.print("\n");

  Serial.print("1 ");
  Serial.print(backDist);
  Serial.print("\n");

  Serial.print("2 ");
  Serial.print(leftDist);
  Serial.print("\n");

  Serial.print("3 ");
  Serial.print(rightDist);
  Serial.print("\n");

  Serial.print("4 ");
  Serial.print(temp);
  Serial.print("\n");

  Serial.print("5 ");
  Serial.print(humidity);
  Serial.print("\n");

  Serial.print("6 ");
  Serial.print(robotAngle);
  Serial.print("\n");

  Serial.print("7 ");
  Serial.print(wet);
  Serial.print("\n");

  Serial.print("8 ");
  Serial.print(controlMode);
  Serial.print("\n");
}

void loop() {
  //lol move this to another thingy
  frontDist = front.readCenti();
  rearDist = rear.readCenti();
  leftDist = left.readCenti();
  rightDist = right.readCenti();
  wet = digitalRead(waterPin);
  
    


  
  sendDataSerial(frontDist, backDist, leftDist, rightDist, temp, humidity, wet, robotAngle, controlMode);
  delay(1000);  
    
}
