#include "drivetrain.h"
#include "FEHLCD.h"

Drivetrain::Drivetrain():
    motorL(FEHMotor::Motor0, 7.2),
    motorR(FEHMotor::Motor1, 7.2),
    timeStamp(0){}

int Drivetrain::stop(void){
    motorL.SetPercent(0);
    motorR.SetPercent(0);

    return 1;
}

int Drivetrain::driveUnbounded(){
    drivePrimitive(SPD, SPD);

    return 0;
}

int Drivetrain::driveDistance(double dist){

    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    drivePrimitive(SPD, SPD);

    if(TimeNowMSec() - timeStamp > dist*INCHES_TO_MSEC){
       timeStamp = 0;
       return stop();
    }

    return 0;
}

int Drivetrain::turnLeft(double deg){
    
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    drivePrimitive(-SPD, SPD);

    if(TimeNowMSec() - timeStamp > deg*DEGREES_TO_MSEC){
       timeStamp = 0;
       return stop();
    }

    return 0;
}

int Drivetrain::turnRight(double deg){
    
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    drivePrimitive(SPD, -SPD);

    if(TimeNowMSec() - timeStamp > deg*DEGREES_TO_MSEC){
        timeStamp = 0;
       return stop();
    }

    return 0;
}

void Drivetrain::drivePrimitive(double lSpd, double rSpd){
    motorL.SetPercent(lSpd*LP + LK);
    motorR.SetPercent(-1*(rSpd*RP + RK));
}