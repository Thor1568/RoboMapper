//DRV855

const int in1 = 2;
const int in2 = 3;
const int in3 = 4;
const int in4 = 5;
const int FLOODWAIT = 500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial init");
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(in1, 255);
  analogWrite(in2, 0);
  analogWrite(in4, 255);
  analogWrite(in3, 0);
  delay(FLOODWAIT);
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in4, 0);
  analogWrite(in3, 0);
  delay(FLOODWAIT);
  analogWrite(in1, 0);
  analogWrite(in2, 255);
  analogWrite(in4, 0);
  analogWrite(in3, 255);
  delay(FLOODWAIT);
}
