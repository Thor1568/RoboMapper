//transisitor stuff

const int TsPin = 11;
int motorPower = 200;
const int TsReadPin = 12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting owo");
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TsPin, HIGH);
  Serial.println(digitalRead(TsReadPin));
  digitalWrite(TsPin, LOW);
  delay(1000);
  Serial.println(digitalRead(TsReadPin));
  delay(1000);
}
