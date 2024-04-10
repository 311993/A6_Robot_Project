#pragma once
#include <FEHMotor.h>
#include <FEHServo.h>
#include <sensor.h>
#include <FEHUtility.h>

using namespace std;

#define MSEC_BOT_TO_TOP 5000/3.75 * 2.8
#define MSEC_BOT_TO_MID 5000/3.75 * 2.1
#define MSEC_TOP_TO_BOT 5000/3.75 * 2.8
#define MSEC_TOP_TO_MID 5000/3.75 * 0.7
#define MSEC_MID_TO_BOT 5000/3.75 * 2.1
#define MSEC_MID_TO_TOP 5000/3.75 * 0.7

#define DEGREES_TO_MSEC 1000.0/190.0

#define LIFT_POW 30
#define UP_POW 35
#define DOWN_POW 30

#define FF_POW 2
#define FF_POW_LUG 5

#define MAX_VOLTAGE 11.7

class Arm{
  public:
    Arm(Sensors sensors);
    int setPos(double theta);
    int botToTop();
    int topToBot();
    int botToMid();
    int topToMid();
    int midToTop();
    int midToBot();

    void liftPrimitive(double pow);

    int hold(bool hasLug);
    int stop();
    int reset();

private:
    FEHMotor motorF;
    Sensors sensors;
    double angle;
    long timeStamp;
};