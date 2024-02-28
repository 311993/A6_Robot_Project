#pragma once
#include <FEHMotor.h>
#include <FEHUtility.h>

using namespace std;

const static double RP = 1, LP = 1.54, RK = 0, LK = 0;
const static double SPD = 50;
const static double DEGREES_TO_MSEC = 5000/580, INCHES_TO_MSEC = 10000/114.0;

class Drivetrain{
  public:
    int driveUnbounded();
    int driveDistance(double dist);
    int turnLeft(double deg);
    int turnRight(double deg);
    int stop(void);
    void drivePrimitive(double rlSpd, double rSpd);
    explicit Drivetrain();
    
  private:  
    FEHMotor motorL;
    FEHMotor motorR;
    long timeStamp;
};