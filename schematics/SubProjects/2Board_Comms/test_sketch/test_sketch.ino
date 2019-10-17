//two board comms testing sketch
boolean transmitting = false;
const int PERIOD = 500;
const int MSGBREAK = 10;
const int msgPin = 9;

int readMsg(int t, int t_break, int aPin) {
  Serial.println(analogRead(aPin));
  return analogRead(aPin)*4;  
}

void sendMsg(int t, int t_break, int aPin, int msg) {
  analogWrite(aPin, msg);
  delay(t/2);
  analogWrite(aPin, 0);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (transmitting) {
    pinMode(msgPin, OUTPUT);
    digitalWrite(msgPin, 0);
  } else {
    pinMode(msgPin, INPUT);  
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (transmitting) {
    sendMsg(PERIOD, MSGBREAK, msgPin, 100);
  } else {
    Serial.println(readMsg(PERIOD, MSGBREAK, msgPin));
  }
}
