#include <main.h>

#define MAX_TIME 1000 * 120

Sensors sensors =  Sensors();
Drivetrain drivetrain = Drivetrain(sensors);
Forklift forklift = Forklift(sensors);
DriveRoutes routes = DriveRoutes(drivetrain);
TaskSequences tasks = TaskSequences(drivetrain, forklift);

int leverNo;
const char *teamKey = "A6TTeNLB5";

int initialize();

int main(void){

int step = 0, timeStep = 0;
long startTime = TimeNowMSec(), timeStamp = TimeNowMSec();

    int x = 0, y = 0;
    while(!LCD.Touch(&x,&y)){
        LCD.WriteLine(Battery.Voltage());//sensors.getRawColor());
        //sensors.sampleColor();
    }
    /*while(!sensors.isLight()){
        //LCD.WriteLine(sensors.getRawColor());
        //Sleep(1);
    }*/

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
                step = routes.startToLevers(leverNo);
            break;
            case 2:
                step = tasks.fuelLever();
                
                /*if(sensors.isLight()){
                    //LCD.WriteLine("here!");
                    routes.color = sensors.isRed();
                }*/
                
            break;
            case 3:            
                drivetrain.stop();
                //step = routes.lightToKiosk();
            break;
            case 4:
                /*drivetrain.drivePrimitive(-50, 50);
                 if(TimeNowMSec() - timeStamp > 5000){
                    step++;

                }*/
                //drivetrain.stop();
                //step+= drivetrain.turnLeft(360);
                //step = routes.kioskToStart();
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
    leverNo = RCS.GetCorrectLever();
    return 1;
}