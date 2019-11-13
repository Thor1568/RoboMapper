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
  int[] message = {};
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
  for (int tick =0; tick<t; tick += t_break/2) {
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
  Serial.println(message);
  return (count - (STRT_MSG+STOP_MSG));
}

void sendOver(int t, int t_break, int apin, int msg) {
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
  //send message parameter
  for (int tick =0; tick<msg; tick++) {
    digitalWrite(apin, HIGH);
    //delays t break / 2 because we need a wave to count so from 0, 1, 0 is one. 0, 1, 0, 1, 0 is two.
    delay(t_break/4);
    digitalWrite(apin, LOW);
    delay(t_break/4); 
  }
  //send stop message
  for (int tick =0; tick<STOP_MSG; tick++) {
    digitalWrite(apin, HIGH);
    delay(t_break/4);
    digitalWrite(apin, LOW);
    delay(t_break/4);  
  }
  int msgLen = STOP_MSG+STRT_MSG+msg;
  int timeToWait = t-(msgLen*(t_break/2));
  delay(timeToWait);
}
