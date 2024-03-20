#pragma once
#include <FEHMotor.h>
#include <FEHServo.h>
#include <sensor.h>
#include <FEHUtility.h>

using namespace std;

#define MSEC_BOT_TO_TOP 577
#define MSEC_BOT_TO_MID 321
#define MSEC_TOP_TO_BOT 500
#define MSEC_TOP_TO_MID 222
#define MSEC_MID_TO_BOT 278
#define MSEC_MID_TO_TOP 256
#define LIFT_POW 50
#define FF_POW 2
#define FF_POW_LUG 5
#define MAX_VOLTAGE 11.7

class Forklift{
  public:
    Forklift(Sensors sensors);
    int botToTop();
    int topToBot();
    int botToMid();
    int topToMid();
    int midToTop();
    int midToBot();

    int hold(bool hasLug);
    int stop();
  private:  
    void liftPrimitive(double pow);
    FEHMotor lift;
    Sensors sensors;
    long timeStamp;
};