  //Message declarations here

//Messages work like this: digital flashes during PERIOD to convey messaage. Summing flash amounts over PERIOD and decoding gives the message sent.
//No messages over a period indicates communication is halted. Could be due to an error or loss of power/connection. Since both sides transmit and recieve, system is half duplex.
//After sending, transmitter waits PERIOD. When communication starts: init msg is recieved, reciver then sends init msg back and then sending data. loop: starts recieving for PERIOD, then waits PERIOD to
//possibly send anything back.

//Ok ignore the above. This saves either 0 or 1 and then turns it to binary.
const int PERIOD = 1000;
//make break at least a tenth of a second for consistency
const int MSGBREAK = 100;


//for ease of testing, upload reciever code first. Press reset buttons at once to ensure good timing mesh.
//SUPER IMPORTANT VARIABLE HERE:
boolean transmitting = true;

//initialize messages
const int END_MSG = 0;
const int INIT_MSG = 1;
const int STRT_MSG = 2;
const int STOP_MSG = 3;
const int TEST_MSG = 4;
const int RIGHTOBJECT = 5;
const int LEFTOBJECT = 6;
const int BACKOBJECT = 7;
const int FRONTOBJECT = 8;
int maxMsgLen = (int) pow(2, PERIOD/MSGBREAK);
int OBJ_DIST;
int TEMP;
int HUMID;

//message value formula is

int code;
int temp;
const int msgPin = 9;

//Abstraction that makes everything work
int readOver(int t, int t_break, int apin) {
  //reads signals over t with t breaks in between signals and turns to binary
  pinMode(apin, INPUT);
  int count = 0;
  int[] message = {0,0,0,0,0,0,0,0,0};
  int val = 0;
  int lastval;
  boolean isMsg = false;
  //we need to wait for an input message
  while (!isMsg) {
    val = digitalRead(apin);
    if (val == 1) {
      isMsg = true;
    }
  }
  //runs for every 2nd t break in t.
  for (int tick =t_break; tick<t; tick += t_break/2) {
    val = digitalRead(apin);
    message[tick] = val;
    //Serial.println(val);
    if (val == 1) {
      Serial.println(message[tick]);
    }

    Serial.print(" tick: ");
    Serial.print(tick);
    Serial.print(" val: ");
    Serial.print(val);
    Serial.print("\n");

    delay(t_break/2);
  }
  Serial.println(calculateBin(message));
  return calculateBin(message);
}

int calculateBin(int msg[]) {
    int sum = 0;
    for (int i =0; i<msg.length(); i++) {
        if(msg[i] == 1) {
            sum += pow(2, i)
        }
    }
    return sum;
}

//return pointer to an array of binary
int* makeBin(int number) {
    int binArr[] = {0,0,0,0,0,0,0,0,0};
    for(int i =0; i<=10; i++) {
        if (number % 2 == 0) {
            number /= 2;
            binArr[i] = 0;
        } else {
            binArr[i] = 1;
            number = number/2;
        }
    }
    return *binArr;
}

void sendOver(int t, int t_break, int apin, int msgArr[]) {
  pinMode(apin, OUTPUT);
  //send start message
  //turn msg to binary

  delayMicroseconds(10);
  for (int tick =0; tick<STRT_MSG; tick++) {
    digitalWrite(apin, HIGH);
    delay(t_break/4);
    digitalWrite(apin, LOW);
    delay(t_break/4);
  }
  //break message and sned it
  for (int i =0; i<msgArr.length(); i++) {
      if (msgArr[i] == 1) {
          digitalWrite(apin, HIGH);
          delay(t_break/4);
          digitalWrite(apin, LOW);
          delay(t_break/4);
      } else {
          digitalWrite(apin, LOW);
          delay(t_break/2);
      }
  }
  int msgLen = STOP_MSG+STRT_MSG+msg;
  int timeToWait = t-(msgLen*(t_break/2));
  delay(timeToWait);
}
