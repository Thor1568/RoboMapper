//Can use #define or const int.
#define SWPIN 2
#define JOYX A0
#define JOYY A1

//1023 is max turn for x or y and 0 is minimum. use map?

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(SWPIN, INPUT);
  digitalWrite(SWPIN, HIGH);
  pinMode(JOYX, INPUT);
  pinMode(JOYY, INPUT);  
  
}

void readJoystick() {
  Serial.print("X axis: ");
  Serial.print(analogRead(JOYX));
  Serial.print("\n");
  Serial.print("Y axis: ");
  Serial.print(analogRead(JOYY));
  Serial.print("\n");
  Serial.print("Button reads: ");
  Serial.print(!digitalRead(SWPIN));
  Serial.print("\n");
}


void loop() {
  // put your main code here, to run repeatedly:
  readJoystick();
  delay(1000);
}
