//sets up one ultrasonic sensor, left
const int u1_trig = 2;
const int u1_echo = 3;
long dur, inches;

//sets up sensor 2 right
const int u2_trig = 12;
const int u2_echo = 11;

//sets up sensor 3, rear
const int u3_trig = 4;
const int u3_echo = 13;

const int FLOODWAIT = 1000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial init");
  pinMode(u1_trig, OUTPUT);
  pinMode(u1_echo, INPUT);
  pinMode(u2_trig, OUTPUT);
  pinMode(u2_echo, INPUT);
  pinMode(u3_trig, OUTPUT);
  pinMode(u3_echo, INPUT);

}

void forward(int in1, int in2, int en, int mySpeed) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(en, mySpeed)
  }

long getDuration(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);  
}

void printFormat(long inches, int sensorNum) {
  Serial.print("Dist of ult sensor ");
  Serial.print(sensorNum);
  Serial.print(": ");
  Serial.print((long)inches);
  Serial.print(" in \n");
  Serial.println("----------------------");
  
}

void printSensorData() {
  dur = getDuration(u1_trig, u1_echo);
  inches = (dur/148.0);
  if (inches > 156) {
    Serial.println("Out of range");
  } else {
      if (inches <= 0.06) {
        Serial.println("owo");  
      } else {
        printFormat(inches, 1);
      }
    }
  

  dur = getDuration(u2_trig, u2_echo);
  inches = (dur/148.0);
  printFormat(inches, 2);

  dur = getDuration(u3_trig, u3_echo);
  inches = (dur/148.0);
  printFormat(inches, 3);
  
}
  

void loop() {
  // put your main code here, to run repeatedly:
  printSensorData();

  delay(FLOODWAIT);
}
