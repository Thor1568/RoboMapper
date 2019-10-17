#include "Arduino.h"
#include "LMotorDriver.h"

LMotorDriver::LMotorDriver(int in1, int in2, int in3, int in4, int ena, int enb) {
    _in1 = in1;
    _in2 = in2;
    _in3 = in3;
    _in4 = in4;
    _ena = ena;
    _enb = enb;
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    pinMode(ena, OUTPUT);
    pinMode(enb, OUTPUT);
}

void LMotorDriver::setSpd(int pwmSpeed) {
    analogWrite(_ena, pwmSpeed);
    analogWrite(_enb, pwmSpeed);
    _speed = pwmSpeed;
}

void LMotorDriver::forward() {
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, LOW);
    digitalWrite(_in3, HIGH);
    digitalWrite(_in4, LOW);
    analogWrite(_ena, _speed);
    analogWrite(_enb, _speed);
}

void LMotorDriver::backward() {
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, HIGH);
    digitalWrite(_in3, LOW);
    digitalWrite(_in4, HIGH);
    analogWrite(_ena, _speed);
    analogWrite(_enb, _speed);
}

void LMotorDriver::left(bool fast) {
    if (fast) {
        digitalWrite(_in1, LOW);
        digitalWrite(_in2, HIGH);
    } else {
        digitalWrite(_in1, LOW);
        digitalWrite(_in2, LOW);
    }
    digitalWrite(_in3, HIGH);
    digitalWrite(_in4, LOW);
    analogWrite(_ena, _speed);
    analogWrite(_enb, _speed);
}

void LMotorDriver::right(bool fast) {

    if (fast) {
        digitalWrite(_in3, LOW);
        digitalWrite(_in4, HIGH);
    } else {
        digitalWrite(_in3, LOW);
        digitalWrite(_in4, LOW);
    }
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, LOW);
    analogWrite(_ena, _speed);
    analogWrite(_enb, _speed);
}

void LMotorDriver::brake() {
    digitalWrite(_in1, HIGH);
    digitalWrite(_in2, HIGH);
    digitalWrite(_in3, HIGH);
    digitalWrite(_in4, HIGH);
}

void LMotorDriver::freeRun() {
    digitalWrite(_ena, LOW);
    digitalWrite(_enb, LOW);
    digitalWrite(_in1, LOW);
    digitalWrite(_in2, LOW);
    digitalWrite(_in3, LOW);
    digitalWrite(_in4, LOW);
}
