/*
Wireless controller for robomapper code
Jobs: print data to LCD, take input from rotary encoder and
from joystick or use keypad


*/
#include <LiquidCrystal.h>

//joystick
#define joyXPin A1
#define joyYPin A0
#define joyBPin 2
int joyX, joyY, joyB;

const int d7 = 3, d6 = 4, d5 = 5, d4 = 6, en = 7, rs = 8;
LiquidCrystal lcd = LiquidCrystal(rs, en, d4, d5, d6, d7);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(joyXPin, INPUT);
  pinMode(joyYPin, INPUT);
  pinMode(joyBPin, INPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("21");
}
//for joystick: if axis is greater than 700 add, if axis is less than 300, subtract


void loop() {
  joyX = analogRead(joyXPin);
  joyY = analogRead(joyYPin);
  joyB = digitalRead(joyBPin);

  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print(joyX);
  lcd.setCursor(0, 1);
  lcd.print(joyY);
  Serial.println(joyX);
  Serial.println(joyY);
  Serial.println("-----------------------------------------------");
  delay(1000);
}

