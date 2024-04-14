#pragma once
#include <FEHMotor.h>
#include <FEHServo.h>
#include <sensor.h>
#include <FEHUtility.h>

using namespace std;

//Define constants
#define DEGREES_TO_MSEC 1000.0/190.0  //msecs per degree of arm rotation
#define LIFT_POW 30 //max power to arm motor
#define MAX_VOLTAGE 11.7 //max battery voltage

//Class representing robot arm mechanism
class Arm{
  public:
    
    Arm(Sensors sensors); //Constructor
    
    //Arm control methods
    int setPos(double theta);
    void liftPrimitive(double pow);
    int stop();
    int reset();

private:

    //Required components
    FEHMotor motorF;
    Sensors sensors;

    //Arm control variables
    double angle; //Current angle from vertical
    long timeStamp; //Time control for arm
};