#ifndef DRVDriver_h
#define DRVDriver_h
#include "Arduino.h"

class DRVDriver
{
public:
    DRVDriver(int inp1, int inp2, int inp3, int inp4, int pwmSpeed);
    void forward(int pwmSpeed);
    void backward(int pwmSpeed);
    void left(int pwmSpeed, bool fast);
    void right(int pwmSpeed, bool fast);
    void freeRun();
    void brake();
private:
    int _in1, _in2, _in3, _in4;
    int _speed;

};

#endif
