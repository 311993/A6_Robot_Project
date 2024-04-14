#include <main.h>

#define MAX_TIME 1000 * 120

Sensors sensors =  Sensors();
Drivetrain drivetrain = Drivetrain(sensors);
Arm arm = Arm(sensors);
DriveRoutes routes = DriveRoutes(drivetrain);
TaskSequences tasks = TaskSequences(drivetrain, arm);

int leverNo = 0;
const char *teamKey = "A6TTeNLB5";

int initialize();
int calibrate();
int manualMech();
int testLevers();
int testPassport();

int main(void){

    int step = 0, timeStep = 0;
    long startTime = TimeNowMSec(), timeStamp = TimeNowMSec();

    //manualMech();
    //calibrate();
    initialize();
    //testLevers();
    //testPassport();

    int x = 0, y = 0;
    /*while(!LCD.Touch(&x,&y)){
        LCD.WriteLine(Battery.Voltage());//sensors.getRawColor());
        //sensors.sampleColor();
        //LCD.WriteLine(sensors.getRawColor());
        //Sleep(1.0);
    }*/
    //Sleep(1.0);

    while(!sensors.isRed() && !LCD.Touch(&x,&y)){
        LCD.WriteLine(sensors.getRawColor());
        Sleep(1);
    }

    while(TimeNowMSec() - startTime < MAX_TIME){
        LCD.WriteLine(step);
        if(timeStep != step){
            timeStep = step;
            timeStamp = TimeNowMSec();
        }
    
        //drivetrain.printEncs();

        switch(step){
            case 0:
                step = 1;
            break;
            case 1:
                step += routes.startToLuggage();
            break;
            case 2:
                step += routes.luggageToLevers(leverNo);
            break;
            case 3:    
                step += tasks.fuelLever(leverNo);        
            break;
            case 4:
                step += routes.leversToKiosk();
            break;
            case 5:
                step += routes.kioskToPassport();
            break;
            case 6:
                step += tasks.stampPassport();
            break;
            case 7:
                step += routes.passportToFinal();
            break;
            case 8:
                arm.stop();
                drivetrain.stop();
            break;
        }

        Sleep(1);
    }

    return 0;
}

int initialize(){
    RCS.InitializeTouchMenu(teamKey);
    leverNo = 0;//RCS.GetCorrectLever();
    return 1;
}