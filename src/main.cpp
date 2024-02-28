#include <main.h>

int step = 0, timeStep = 0;
long startTime = TimeNowMSec(), timeStamp = TimeNowMSec();
const long MAX_TIME = 1000 * 120;

int leverNo;
const char teamKey;

int main(void){

    int x = 0, y = 0;
    while(!LCD.Touch(&x,&y)){}

    while(TimeNowMSec() - startTime < MAX_TIME){

        if(timeStep != step){
            timeStep = step;
            timeStamp = TimeNowMSec();
        }

        switch(step){
            case 0:
                step = initialize();
            break;
            case 1:
                step = Drivetrain::driveUnbounded(0.2);
            break;
        }

        Sleep(50);
    }

    return 0;
}

int initialize(){
    RCS.InitializeTouchMenu(&teamKey);
    return 1;
}