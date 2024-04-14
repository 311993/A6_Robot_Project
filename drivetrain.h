#pragma once
#include <FEHMotor.h>
#include <FEHUtility.h>
#include <sensor.h>

using namespace std;

//Define constants
#define RP 1    //Right-side roportional control
#define LP 1.07 //Left-side proportional control
#define RK 0    //Right-side constant control
#define LK 0    //Left-side constant control

#define SPD 50  //Standard drive speed
#define MAX_VOLTAGE 11.7 //Max battery voltage

#define DEGREES_TO_MSEC 5000/447.0 * 390/315.0 //msecs per degree of turn
#define INCHES_TO_MSEC 10000/78.0 //msecs per inch of driving

#define INCHES_TO_TICKS (24.0/25.0) * 48.0 * (108.0/109.0) / (2.75*3.14159) //ticks per inch of driving
#define DEGREES_TO_TICKS_L  0.3625 //ticks per degree of a left turn
#define DEGREES_TO_TICKS_R  0.3750 //ticks per degree of a right turn

//Class representing robot drivetrain
class Drivetrain{

  public:

    Drivetrain(Sensors sensors); //Constructor

    //Evaluatory methods
    void printEncs();
    int breakTime(double mSec);
    int breakEnc(double ticks);

    //Basic drive methods
    int driveUnbounded();
    int wait(double mSec);
    int stop(void);
    void drivePrimitive(double lSpd, double rSpd);

    //Controlled drive methods
    int driveDistance(double dist);
    int driveTime(double pow, int msec);
    int driveBack(double dist);
    int turnLeft(double deg);
    int turnRight(double deg);
    int align();

    //Required components
    Sensors sensors;

private:  

    //Required components
    FEHMotor motorL;
    FEHMotor motorR;
    DigitalEncoder encL;
    DigitalEncoder encR;

    //Control variables
    long timeStamp; //Time control for drivetrain
    const static bool useEnc = true; //Whether to use encoders
};