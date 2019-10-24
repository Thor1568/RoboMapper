const int v1Pin = A0;
const int v2Pin = A1;
int tempVolts;

//https://www.allaboutcircuits.com/projects/make-a-digital-voltmeter-using-the-arduino/
//bruh this isn't working 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("ArduVoltmeter xd");
}

float getVoltage(int analogVal, float maxVoltage) {
  float finalVolts = (analogVal*maxVoltage)/1024.0;
  return finalVolts;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Voltages are");
  tempVolts = getVoltage(analogRead(v1Pin), 5);
  Serial.print("v1: ");
  Serial.print(tempVolts);
  Serial.print("\n");
  Serial.print("v2: ");
  tempVolts = getVoltage(analogRead(v2Pin), 7.4);
  Serial.print(tempVolts);
  Serial.print("\n");
  delay(1000);
}


