#pragma once
//#include <forklift.h>
#include <drivetrain.h>
#include <sensor.h>
#include <FEHLCD.h>
#include <FEHRCS.h>

using namespace std;

class DriveRoutes{
  public:
    DriveRoutes(Drivetrain drivetrain);
    int startToKiosk();
  private:
    Drivetrain drivetrain;
    int substep = 0;
    long subTimeStamp = 0;
};

class TaskSequences{
  public:
  private:  
};