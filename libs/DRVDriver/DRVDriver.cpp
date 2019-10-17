#include "Arduino.h"
#include "DRVDriver.h"

DRVDriver::DRVDriver(int inp1, int inp2, int inp3, int inp4, int pwmSpeed) {
    _in1 = inp1;
    _in2 = inp2;
    _in3 = inp3;
    _in4 = inp4;
    pinMode(_in1, OUTPUT);
    pinMode(_in2, OUTPUT);
    pinMode(_in3, OUTPUT);
    pinMode(_in4, OUTPUT);
    _speed = pwmSpeed;

}

void DRVDriver::forward(int pwmSpeed) {
    _speed = pwmSpeed;
    digitalWrite(_in2, LOW);
    analogWrite(_in1, pwmSpeed);
    digitalWrite(_in4, LOW);
    analogWrite(_in3, pwmSpeed);
}

void DRVDriver::backward(int pwmSpeed) {
    _speed = pwmSpeed;
    digitalWrite(_in1, LOW);
    analogWrite(_in2, pwmSpeed);
    digitalWrite(_in3, LOW);
    analogWrite(_in4, pwmSpeed);
}

void DRVDriver::left(int pwmSpeed, bool fast) {
    _speed = pwmSpeed;
    if (fast) {
        digitalWrite(_in2, LOW);
        analogWrite(_in1, HIGH);
        digitalWrite(_in4, HIGH);
        analogWrite(_in3, LOW);
    } else {
        digitalWrite(_in2, LOW);
        analogWrite(_in1, HIGH);
        digitalWrite(_in4, LOW);
        analogWrite(_in3, LOW);
    }
}

void DRVDriver::right(int pwmSpeed, bool fast) {
    _speed = pwmSpeed;
    if (fast) {
        digitalWrite(_in2, HIGH);
        analogWrite(_in1, LOW);
        digitalWrite(_in4, LOW);
        analogWrite(_in3, HIGH);
    } else {
        digitalWrite(_in2, LOW);
        analogWrite(_in1, LOW);
        digitalWrite(_in4, LOW);
        analogWrite(_in3, HIGH);
    }
}

void DRVDriver::freeRun() {
    _speed = 0;
    digitalWrite(_in2, LOW);
    analogWrite(_in1, LOW);
    digitalWrite(_in4, LOW);
    analogWrite(_in3, LOW);
}

void DRVDriver::brake() {
    _speed = 0;
    digitalWrite(_in2, HIGH);
    analogWrite(_in1, HIGH);
    digitalWrite(_in4, HIGH);
    analogWrite(_in3, HIGH);
}
