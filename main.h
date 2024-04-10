#pragma once
#include <mech.h>
#include <drivetrain.h>
#include <sensor.h>
#include <FEHLCD.h>
#include <FEHRCS.h>

using namespace std;

class DriveRoutes{
  public:
    DriveRoutes(Drivetrain drivetrain);
    int startToLuggage();
    int luggageToLevers(int leverNo);
    int leversToKiosk();
    int kioskToPassport();
    int passportToFinal();
    int color; //1 = red, 0 = blue

private:
    Drivetrain drivetrain;
    int substep = 0;
    long subTimeStamp = 0;
};

class TaskSequences{
  public:
    TaskSequences(Drivetrain drivetrain, Arm forklift);
    int stampPassport();
    int fuelLever(int leverNo);

private:  
    Drivetrain drivetrain;
    Arm forklift;
    int substep = 0;
    long subTimeStamp = 0;
};