//functions here
void mForward(int t) {
  d.forward();
  delay(t);
  d.brake();  
}

void mBackward(int t) {
  d.backward();
  delay(t);
  d.brake();  
}

void mForward() {
  d.forward();
  d.brake();  
}

void mBackward() {
  d.backward();
  d.brake();  
}

void mLeft90() {
  d.left(true);
  delay(400);
  d.brake();  
} 

void mRight90() {
  d.right(true);
  delay(400);
  d.brake();  
} 

int getMiddlePosition(int leftDist, int rightDist) {
  return leftDist+rightDist;  
}



//Setup function
void setup() {
  Serial.begin(9600);
  Serial.println("Navigation subproject running...");
  d.setSpd(s);
}

