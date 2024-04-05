#include <main.h>

#define MAX_TIME 1000 * 120

Sensors sensors =  Sensors();
Drivetrain drivetrain = Drivetrain(sensors);
Forklift forklift = Forklift(sensors);
DriveRoutes routes = DriveRoutes(drivetrain);
TaskSequences tasks = TaskSequences(drivetrain, forklift);

int leverNo = 0;
const char *teamKey = "A6TTeNLB5";

int initialize();
int calibrate();
int manualMech();

int main(void){

    int step = 0, timeStep = 0;
    long startTime = TimeNowMSec(), timeStamp = TimeNowMSec();

    //manualMech();
    //calibrate();
    //initialize();

    int x = 0, y = 0;
    /*while(!LCD.Touch(&x,&y)){
        LCD.WriteLine(Battery.Voltage());//sensors.getRawColor());
        //sensors.sampleColor();
        //LCD.WriteLine(sensors.getRawColor());
        //Sleep(1.0);
    }*/
    //Sleep(1.0);
    while(!sensors.isLight() && !LCD.Touch(&x,&y)){
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
                //drivetrain.drivePrimitive(50, 0);
                step = 1;
            break;
            case 1:
                //step += drivetrain.turnLeft(360);
                //step++;
                //forklift.liftPrimitive(-30);
                /*if(TimeNowMSec() - timeStamp > 5000){
                    step++;
                }*/
                //step+=forklift.botToTop();
                step = routes.startToLuggage();
            break;
            case 2:
                //forklift.stop();
                //step = tasks.stampPassport();
                step = routes.luggageToFinal();

                /*if(sensors.isLight()){
                    //LCD.WriteLine("here!");
                    routes.color = sensors.isRed();
                }*/
                //step+=forklift.topToBot();
            break;
            case 3:    
                drivetrain.stop();        
                /*drivetrain.drivePrimitive(50, 0);

                if(TimeNowMSec() - timeStamp > 5000){
                    step++;

                }*/

                //step = routes.lightToKiosk();
            break;
            case 4:
                
                drivetrain.drivePrimitive(50, -50);

                if(TimeNowMSec() - timeStamp > 5000){
                    step++;

                }

                /*drivetrain.drivePrimitive(-50, 50);
                 if(TimeNowMSec() - timeStamp > 5000){
                    step++;
                
                }*/
                //drivetrain.stop();
                //step+= drivetrain.turnLeft(360);
                //step = routes.kioskToStart();
            break;
            case 5:
                
                drivetrain.drivePrimitive(0, 50);

                if(TimeNowMSec() - timeStamp > 200){
                    step++;

                }

            break;
            case 6:

                drivetrain.drivePrimitive(50, 0);

                if(TimeNowMSec() - timeStamp > 5000){
                    step++;

                }

            break;
            case 7:
                forklift.stop();
                drivetrain.stop();
            break;
        }

        //sensors.sampleColor();
        Sleep(1);
    }

    return 0;
}

int initialize(){
    RCS.InitializeTouchMenu(teamKey);
    leverNo = RCS.GetCorrectLever();
    return 1;
}

int calibrate(){
    int x = 0, y = 0;

        while(!LCD.Touch(&x,&y)){}
    while(!forklift.setPos(-90)){}
        while(!LCD.Touch(&x,&y)){}
    while(!forklift.setPos(90)){}
        while(!LCD.Touch(&x,&y)){}
    while(!forklift.setPos(0)){}
        while(true){}

        while(!LCD.Touch(&x,&y)){}
    while(!drivetrain.driveDistance(12*9)){drivetrain.printEncs();}
        while(!LCD.Touch(&x,&y)){}
    while(!drivetrain.turnLeft(360)){drivetrain.printEncs();}
        while(!LCD.Touch(&x,&y)){}
    while(!drivetrain.turnRight(360)){drivetrain.printEncs();}
        while(true){}
}

int manualMech(){
    int x = 0, y = 0;
    LCD.Clear();
    LCD.WriteAt('L', 80, 120);
    LCD.WriteAt('R', 240, 120);

    while(true){

        if(LCD.Touch(&x, &y)){
            forklift.liftPrimitive( x > 160 ? 50 : -50);
        }else{
            forklift.liftPrimitive(0);
        }

        Sleep(20);
    }
}