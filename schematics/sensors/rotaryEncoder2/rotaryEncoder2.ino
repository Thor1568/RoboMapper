const int clkPin= 2; //the clk attach to pin 2
const int dtPin= 3; //the dt pin attach to pin 3
const int swPin= 4 ;//the sw pin attach to pin 4

int encoderVal = 0;

 

void setup() {
//set clkPin,dePin,swPin as INPUT
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT);
  digitalWrite(swPin, HIGH);
  Serial.begin(9600); // initialize serial communications at 9600 bps

}

 

void loop() {
  int change = getEncoderTurn();//
  encoderVal = encoderVal + change;
  if(digitalRead(swPin) == LOW) {//if button pull down {
    encoderVal = 0;
  }
  Serial.println(encoderVal);
}


int getEncoderTurn(void) {
  static int oldA = HIGH; //set the oldA as HIGH
  static int oldB = HIGH; //set the oldB as HIGH
  int result = 0;
  int newA = digitalRead(clkPin);//read the value of clkPin to newA
  int newB = digitalRead(dtPin);//read the value of dtPin to newB
  if (newA != oldA || newB != oldB){ //if the value of clkPin or the dtPin has changed
  // something has changed
    if (oldA == HIGH && newA == LOW) {
      result = (oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  return result;
}
