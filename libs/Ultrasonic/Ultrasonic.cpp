#include "Arduino.h"
#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int echoPin, int trigPin) {
    _echoPin = echoPin;
    _trigPin = trigPin;
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);

}

double Ultrasonic::readInches() {
    temp = readS();
    temp = (temp/2)/74.0;
    return temp;
}

double Ultrasonic::readS() {
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);
    return pulseIn(_echoPin, HIGH);
}
double Ultrasonic::getAccDist(double temp) {
    double dur = readS();
    double spdSnd = (331.4+0.6*temp)/10000//Calculate the speed of sound based on temperature in cm/microseconds. 343m/s
    double dist = (dur/2)*spdSnd
}

double Ultrasonic::readCenti() {
    temp = readS();
    temp = temp/(29.1*2);
    return temp;
}
