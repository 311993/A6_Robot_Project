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
    leverNo = RCS.GetCorrectLever();
    return 1;
}

int calibrate(){
    int x = 0, y = 0;

        while(!LCD.Touch(&x,&y)){}
    while(!arm.setPos(-90)){}
        while(!LCD.Touch(&x,&y)){}
    while(!arm.setPos(90)){}
        while(!LCD.Touch(&x,&y)){}
    while(!arm.setPos(0)){}
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
            arm.liftPrimitive( x > 160 ? 50 : -50);
        }else{
            arm.liftPrimitive(0);
        }

        Sleep(20);
    }
}