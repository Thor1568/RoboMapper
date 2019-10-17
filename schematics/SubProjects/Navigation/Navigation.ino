#include <LMotorDriver.h>

//motor variables
const int in1 = 8;
const int in2 = 9;
const int ena = 10;
const int in3 = 7;
const int in4 = 6;
const int enb = 5;
//motor speed, can be changed
const int s = 160;
//Motor wait that is used in motor functions
const int w = 100;

//Navigation variables
//choice 0 means move forwards and avoid things ahead
int choice = 0;
int frontDist, leftDist, rightDist;
int lastFrontDist, lastLeftDist, lastRightDist;


//motor driver object
LMotorDriver d(in1, in2, in3, in4, ena, enb);



