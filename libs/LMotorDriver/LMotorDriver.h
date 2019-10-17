#ifndef LMotorDriver_h
#define LMotorDriver_h

class LMotorDriver
{
public:
    LMotorDriver(int in1, int in2, int in3, int in4, int ena, int enb);
    void forward();
    void backward();
    void left(bool fast);
    void right(bool fast);
    void freeRun();
    void brake();
    void setSpd(int pwmSpeed);

private:
    int _in1, _in2, _in3, _in4, _ena, _enb, _speed;
};

#endif
