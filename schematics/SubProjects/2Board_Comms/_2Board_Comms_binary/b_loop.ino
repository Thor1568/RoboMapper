//Loop structure for recieving end:
//the code recieved over period
int MsgToSnd = TEST_MSG;
boolean doSend = true;
void recieve() {
  code = readOver(PERIOD, MSGBREAK, msgPin);
  switch(code) {
    case TEST_MSG:
      Serial.println("Yay! it worked!");
      sendOver(PERIOD, MSGBREAK, msgPin, END_MSG);
      break;

    case INIT_MSG:
      Serial.println("Init msg? Maybe error");
      break;
    
    case END_MSG:
      Serial.println("Ended.");
      break;
    default:
      Serial.println("Other stuff?");
      Serial.print("Value recieved:");
      Serial.print(code);
      Serial.print("\n");
      break;
      
  } 
}

void transmit() {
  while (doSend) {
    sendOver(PERIOD, MSGBREAK, msgPin, MsgToSnd);
    Serial.println("Message sent");
    temp = readOver(PERIOD, MSGBREAK, msgPin);
    pinMode(msgPin, OUTPUT); 
    Serial.println("Normal transmit");Serial.println("recieved: ");
    Serial.println(temp);
    if (temp == 0) {
      doSend = false;
      Serial.println("Reciever sent quit"); 
      sendOver(PERIOD, MSGBREAK, msgPin, END_MSG);
    }
  }  
}

void transmit2() {
  sendOver(PERIOD, MSGBREAK, msgPin, MsgToSnd);
  Serial.println("Message sent");  
}

//actual loop
void loop() { 
  if (transmitting) {
    transmit2();
    //transmit();  
  } else {
    recieve();  
  }
}


