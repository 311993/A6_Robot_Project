#pragma once
#include <FEHMotor.h>
#include <FEHUtility.h>
#include <sensor.h>

using namespace std;

#define RP 1
#define LP 1.07
#define RK 0
#define LK 0
#define SPD 50
#define MAX_VOLTAGE 11.7
#define DEGREES_TO_MSEC 5000/447.0 * 390/315.0
#define INCHES_TO_MSEC 10000/78.0
#define INCHES_TO_TICKS (24.0/25.0) * 48.0 * (108.0/109.0) / (2.75*3.14159)
#define DEGREES_TO_TICKS (330.0/360.0) * 48.0 / (1.5*2.75*3.14159*9.5)
#define LTURNP 333.0/360.0

class Drivetrain{
  public:
    int driveUnbounded();
    int wait(double mSec);
    int driveDistance(double dist);
    int driveTime(double pow, int msec);
    int drivePower(double pow, double dist);
    int drivePower(double pow, int msec);
    int driveBack(double dist);
    int turnLeft(double deg);
    int turnRight(double deg);
    int followLine();
    int driveUntilLine();
    int driveUntilBump();
    int stop(void);
    int breakTime(double mSec);
    int breakEnc(double ticks);
    void drivePrimitive(double lSpd, double rSpd);
    Drivetrain(Sensors sensors);

    void printEncs();

private:  
    FEHMotor motorL;
    FEHMotor motorR;
    DigitalEncoder encL;
    DigitalEncoder encR;
    Sensors sensors;
    long timeStamp;
    const static bool useEnc = true;
};