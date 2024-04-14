#pragma once
#include <mech.h>
#include <drivetrain.h>
#include <sensor.h>
#include <FEHLCD.h>
#include <FEHRCS.h>

using namespace std;

//Define constants
#define MAX_TIME 1000 * 120 //The max run time: 2 min = 120,000 msecs

//A class that contains command sequences only involving the drivetrain
class DriveRoutes{

  public:
    
    DriveRoutes(Drivetrain drivetrain); //Constructor
    
    //Driving routes
    int startToLuggage();
    int luggageToLevers(int leverNo);
    int leversToKiosk();
    int kioskToPassport();
    int passportToFinal();
    
    int color; //Light color: 1 = red, 0 = blue

  private:
    
    //Required subsystems
    Drivetrain drivetrain;
    
    //Control variables
    int substep = 0; //State of subsequence
    long subTimeStamp = 0; //Time control for subsequence
};

//A class that contains command sequences that involve both the arm and drivetrain
class TaskSequences{

  public:
    
    TaskSequences(Drivetrain drivetrain, Arm arm); //Constructor

    //Task subsequences
    int stampPassport();
    int fuelLever(int leverNo);

  private:  

    //Required subsystems
    Drivetrain drivetrain;
    Arm arm;
    
    //Control variables
    int substep = 0; //State of subsequence
    long subTimeStamp = 0; //Time control for subsequence
};