//if we have recieved start to exit setup and go to mainloop
boolean recievedStart = false;
int ans = 0;
//temporary starting value
boolean tempStart = false;

void setup() {
  Serial.begin(9600);
  Serial.println(MAX_MSG);
  Serial.println("Ready to start!");
  pinMode(msgPin, OUTPUT);
  digitalWrite(msgPin, LOW);
  /*
  Serial.println("Enter y to start");
  Serial.setTimeout(10000);
  while (!tempStart) {
    response = Serial.readString();
    if (response == "y") {
      break;  
    }
  }
  */
  //test code
  if (transmitting) {
    while (true) {
      pinMode(msgPin, OUTPUT);
      sendOver(PERIOD, MSGBREAK, msgPin, RIGHTOBJECT);
      //delay(PERIOD);
    }
  } else {
    while (true) {
      pinMode(msgPin, INPUT);
      ans = readOver(PERIOD, MSGBREAK, msgPin);
      Serial.println(ans);
    }
  }


  
  if (transmitting) {
    //if we are transmitting, we wait for an answer from the reciever and send it the init message to say we are ready
    while (ans != INIT_MSG) {
      pinMode(msgPin, OUTPUT);
      sendOver(PERIOD, MSGBREAK, msgPin, INIT_MSG);
      pinMode(msgPin, INPUT);
      ans = readOver(PERIOD, MSGBREAK, msgPin);
      Serial.println("transmitter waiting");
      Serial.println(ans);
    }
  } else {
    //reciever code
    //reset pin to input every time becuase read and send change pin property
      while(!recievedStart) {
        //while we haven't started, we read and then if we read start, we 
        pinMode(msgPin, INPUT);
        temp = readOver(PERIOD, MSGBREAK, msgPin);
        Serial.println(temp);
        if (temp == INIT_MSG) {
          recievedStart = true;
          pinMode(msgPin, OUTPUT);
          sendOver(PERIOD, MSGBREAK, msgPin, INIT_MSG);
          break;
        //then we quit to main loop because we have connection confirmation
        }
      }
    }    
}
