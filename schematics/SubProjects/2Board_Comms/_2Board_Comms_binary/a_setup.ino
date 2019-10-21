
void setup() {
  Serial.begin(9600);
  Serial.println("Ready to start!");
  pinMode(msgPin, OUTPUT);
  digitalWrite(msgPin, LOW);

  
}
