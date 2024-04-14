#include <main.h>

//Construct instances of robot systems and sequences
Sensors sensors =  Sensors();
Drivetrain drivetrain = Drivetrain(sensors);
Arm arm = Arm(sensors);
DriveRoutes routes = DriveRoutes(drivetrain);
TaskSequences tasks = TaskSequences(drivetrain, arm);

//Define RCS constants
int leverNo = 0;
const char *teamKey = "A6TTeNLB5";

int initialize();

int main(void){

    //Define time and state control variables
    int step = 0, timeStep = 0;
    long startTime = TimeNowMSec(), timeStamp = TimeNowMSec();

    //Connect to RCS
    initialize();
   
    int x = 0, y = 0;

    //Wait for start light or touch (for testing purposes only)
    while(!sensors.isRed() && !LCD.Touch(&x,&y)){

        //Display CDS data to check calibration
        LCD.WriteLine(sensors.getRawColor());
        Sleep(1);
    }

    //Main robot loop: Run until timeout or shutdown
    while(TimeNowMSec() - startTime < MAX_TIME){

        //Display robot state
        LCD.WriteLine(step);
        
        //Reset timing control after a time-controlled step has executed (Such a step was not used in the final main loop)
        if(timeStep != step){
            timeStep = step;
            timeStamp = TimeNowMSec();
        }

        //Execute a sequence of commands based on robot state
        switch(step){
            case 0:
                step = 1; //Skip the 0th step
            break;

            case 1:
                step += routes.startToLuggage(); //Press start button and deposit luggage
            break;
            
            case 2:
                step += routes.luggageToLevers(leverNo); //Move from luggage depot to fuel levers
            break;
            
            case 3:    
                step += tasks.fuelLever(leverNo); //Flip fuel lever task
            break;
            
            case 4:
                step += routes.leversToKiosk(); //Move from fuel levers to kiosk button press
            break;
            
            case 5:
                step += routes.kioskToPassport(); //Move from kiosk to in front of passport
            break;
            
            case 6:
                step += tasks.stampPassport(); //Stamp passport task
            break;
            
            case 7:
                step += routes.passportToFinal(); //Move from passport to hit final button
            break;
            
            case 8:                             //Stop all motors
                arm.stop();
                drivetrain.stop();
            break;
        }

        //Wait min cycle time to reduce unnecessary load on proteus
        Sleep(1);
    }

    //Success error code
    return 0;
}

//Connect to RCS and run RCS initialization
int initialize(){
    RCS.InitializeTouchMenu(teamKey);
    leverNo = RCS.GetCorrectLever();
    return 1;
}