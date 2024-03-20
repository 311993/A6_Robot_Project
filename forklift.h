#pragma once
#include <FEHMotor.h>
#include <FEHServo.h>
#include <sensor.h>
#include <FEHUtility.h>

using namespace std;

#define MSEC_TO_TOP 577
#define MSEC_TO_BOT 500
#define LIFT_POW 50
#define FF_POW 2
#define FF_POW_LUG 5

class Forklift{
  public:
    Forklift(Sensors sensors);
    int toTop();
    int toBot();
    int hold(bool hasLug);
    int stop();
  private:  
    void liftPrimitive(double pow);
    FEHMotor lift;
    Sensors sensors;
    long timeStamp;
};