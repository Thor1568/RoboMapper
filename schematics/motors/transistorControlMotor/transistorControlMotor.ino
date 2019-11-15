//transisitor stuff

const int TsPin = 13;
int motorPower = 200;
const int TsReadPin = 12;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Starting owo");
  pinMode(TsPin, OUTPUT);
  pinMode(TsReadPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TsPin, HIGH);
  Serial.println("Ts Pin is high");
  Serial.println(digitalRead(TsReadPin));
  delay(1000);
  digitalWrite(TsPin, LOW);
  Serial.println("Ts Pin is low");
  Serial.println(digitalRead(TsReadPin));
  delay(1000);
}
