#pragma once
#include <FEHMotor.h>
#include <FEHUtility.h>
#include <sensor.h>

using namespace std;

#define RP 1
#define LP 1.28
#define RK 0
#define LK 0
#define SPD 50
#define MAX_VOLTAGE 11.7
#define DEGREES_TO_MSEC 5000/447.0 * 390/315.0
#define INCHES_TO_MSEC 10000/78.0

class Drivetrain{
  public:
    int driveUnbounded();
    int wait(double mSec);
    int driveDistance(double dist);
    int driveBack(double dist);
    int turnLeft(double deg);
    int turnRight(double deg);
    int followLine();
    int driveUntilLine();
    int driveUntilBump();
    int stop(void);
    int manageTime(double mSec);
    void drivePrimitive(double rlSpd, double rSpd);
    Drivetrain(Sensors sensors);
    
  private:  
    FEHMotor motorL;
    FEHMotor motorR;
    Sensors sensors;
    long timeStamp;
};