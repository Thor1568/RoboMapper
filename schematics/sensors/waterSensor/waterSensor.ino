const int waterSensPin = 4;
const int FLOODWAIT = 500;
int digval;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Program start: water sensor");
  pinMode(waterSensPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digval = digitalRead(waterSensPin);
  Serial.print("Rain? ");
  if (digval == 1) {
    Serial.print("yes");
  } else {
    Serial.print("no");
  }
  
  Serial.print("\n");
  delay(FLOODWAIT);
}
