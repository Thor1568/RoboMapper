/*
Wireless controller for robomapper code
Jobs: print data to LCD, take input from rotary encoder and
from joystick or use keypad


*/

//joystick
#define joyXPin A1
#define joyYPin A0
#define joyBPin 2
int joyX, joyY, joyB;

void setup() {
  // put your setup code here, to run once:
  pinMode(joyXPin, INPUT);
  pinMode(joyYPin, INPUT);
  pinMode(joyBPin, INPUT);
}


