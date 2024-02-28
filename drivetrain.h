#pragma once
#include <FEHMotor.h>
#include <FEHUtility.h>

using namespace std;

FEHMotor motorL(FEHMotor::Motor0, 7.2);
FEHMotor motorR(FEHMotor::Motor1, 7.2);

class Drivetrain{
  public:
    static int driveUnbounded(double spd){}
    static int driveDistance(double dist, double spd){}
    static int turnLeft(double deg, double spd){}
    static int turnRight(double deg, double spd){}
    static int stop(void);
  private:  
    static void drivePrimitive(double rlSpd, double rSpd){}
    const static double RP, LP, RK, LK;
    const static double FULL_SPEED;
    const static double DEGREES_TO_MSEC, INCHES_TO_MSEC;
    static long timeStamp;
};