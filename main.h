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
};

class TaskSequences{
  public:
  private:  
};