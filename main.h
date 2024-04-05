#pragma once
#include <forklift.h>
#include <drivetrain.h>
#include <sensor.h>
#include <FEHLCD.h>
#include <FEHRCS.h>

using namespace std;

class DriveRoutes{
  public:
    DriveRoutes(Drivetrain drivetrain);
    int startToLuggage();
    int luggageToFinal();
    int upperToPassport();
    int startToLevers(int leverNo);
    int startToKiosk();
    int startToUpper();
    int findLight();
    int upperToLight();
    int lightToKiosk();
    int kioskToStart();
    int color; //1 = red, 0 = blue

private:
    Drivetrain drivetrain;
    int substep = 0;
    long subTimeStamp = 0;
};

class TaskSequences{
  public:
    TaskSequences(Drivetrain drivetrain, Forklift forklift);
    int stampPassport();
    int fuelLever();

private:  
    Drivetrain drivetrain;
    Forklift forklift;
    int substep = 0;
    long subTimeStamp = 0;
};