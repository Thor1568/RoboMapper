//Accelerometer on MEGA2560
#include <Wire.h>

//Hex addresss for sensor I2C
int gyAccel = 0x68;

float x_out, y_out, z_out;
int temperature;
float x2_out, y2_out, z2_out;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Start");
  //Starts I2C and sets measuring mode for gyAccel
  Wire.begin();
  Wire.beginTransmission(gyAccel);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  delay(10);
}

void readSensor() {
  Wire.beginTransmission(gyAccel);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(gyAccel, 7*2, true);
  x_out = (Wire.read() | Wire.read() << 8);
  y_out = (Wire.read() | Wire.read() << 8);
  z_out = (Wire.read() | Wire.read() << 8);
  temperature = (Wire.read() | Wire.read() << 8);
  x2_out = (Wire.read() | Wire.read() << 8);
  y2_out = (Wire.read() | Wire.read() << 8);
  z2_out = (Wire.read() | Wire.read() << 8);
  x2_out /= 256;
  y2_out /= 256;
  z2_out /= 256;  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  readSensor();
  Serial.print("---------------------- \n");
  Serial.print("X: ");
  Serial.print(x_out);
  Serial.print(" Y: ");
  Serial.print(y_out);
  Serial.print(" Z: ");
  Serial.print(z_out);

  
}
