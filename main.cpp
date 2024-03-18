#include <main.h>
#include "FEHBattery.h"

#define MAX_TIME 1000 * 120

Sensors sensors =  Sensors();
Drivetrain drivetrain = Drivetrain(sensors);
DriveRoutes routes = DriveRoutes(drivetrain);

int initialize();

int main(void){

int step = 0, timeStep = 0;
long startTime = TimeNowMSec(), timeStamp = TimeNowMSec();

int leverNo;
const char *teamKey = "A6TTeNLB5";

    int x = 0, y = 0;
    /*while(!LCD.Touch(&x,&y)){
        LCD.WriteLine(sensors.getRawColor());
        //sensors.sampleColor();
    }*/
    while(!sensors.isLight()){
        //LCD.WriteLine(sensors.getRawColor());
        //Sleep(1);
    }

    while(TimeNowMSec() - startTime < MAX_TIME){
        //LCD.WriteLine(Battery.Voltage());
        if(timeStep != step){
            timeStep = step;
            timeStamp = TimeNowMSec();
        }

        switch(step){
            case 0:
                step = initialize();
            break;
            case 1:
                //step += drivetrain.turnLeft(360);
                //step++;
                step = routes.startToUpper();
            break;
            case 2:
                step = routes.upperToLight();
                
                if(sensors.isLight()){
                    //LCD.WriteLine("here!");
                    routes.color = sensors.isRed();
                }
                
            break;
            case 3:
                step = routes.lightToKiosk();
            break;
            case 4:
                /*drivetrain.drivePrimitive(-50, 50);
                 if(TimeNowMSec() - timeStamp > 5000){
                    step++;

                }*/
                //drivetrain.stop();
                //step+= drivetrain.turnLeft(360);
                step = routes.kioskToStart();
            break;
            case 5:
                drivetrain.stop();
            break;
        }

        //sensors.sampleColor();
        Sleep(1);
    }

    return 0;
}

int initialize(){
    //RCS.InitializeTouchMenu(&teamKey);
    return 1;
}