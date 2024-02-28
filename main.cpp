#include <main.h>
#include "FEHBattery.h"

const long MAX_TIME = 1000 * 120;
Drivetrain drivetrain = Drivetrain();
DriveRoutes routes = DriveRoutes(drivetrain);
Sensors sensors =  Sensors();

int initialize();

int main(void){

int step = 0, timeStep = 0;
long startTime = TimeNowMSec(), timeStamp = TimeNowMSec();

int leverNo;
const char teamKey = '6';

    int x = 0, y = 0;
    while(!LCD.Touch(&x,&y)){}
    //while(!sensors.isLight(){}

    while(TimeNowMSec() - startTime < MAX_TIME){
        //LCD.WriteLine(step);
        if(timeStep != step){
            timeStep = step;
            timeStamp = TimeNowMSec();
        }

        switch(step){
            case 0:
                step = initialize();
            break;
            case 1:
                //step += drivetrain.driveDistance(12);
                //step++;
                step = routes.startToKiosk();
            break;
            case 2:
                /*drivetrain.drivePrimitive(-50, 50);
                 if(TimeNowMSec() - timeStamp > 5000){
                    step++;

                }
                //drivetrain.stop();*/
            break;
            case 3:
                //drivetrain.stop();
            break;
        }

        sensors.sampleColor();
        Sleep(20);
    }

    return 0;
}

int initialize(){
    //RCS.InitializeTouchMenu(&teamKey);
    return 1;
}