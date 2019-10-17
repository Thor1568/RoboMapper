#ifndef Ultrasonic_h
#define Ultrasonic_h
#include "Arduino.h"

class Ultrasonic {
public:
    Ultrasonic(int echoPin, int trigPin);
    double readInches();
    double read();
    double getAccDist(double temp);
    double readCenti();
private:
    int _echoPin, _trigPin;
};

#endif
