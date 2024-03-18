#include "drivetrain.h"
#include "FEHLCD.h"

Drivetrain::Drivetrain(Sensors sensors):
    motorL(FEHMotor::Motor0, 7.2),
    motorR(FEHMotor::Motor1, 7.2),
    sensors(sensors),
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

int Drivetrain::wait(double mSec){
    stop();

     if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    if(TimeNowMSec() - timeStamp > mSec){
       timeStamp = 0;
       return stop();
    }
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

int Drivetrain::driveBack(double dist){

    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    drivePrimitive(-SPD, -SPD);

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

int Drivetrain::driveUntilBump(){
    drivePrimitive(SPD, SPD);

    if(sensors.getBump()){
        timeStamp = 0;
        return stop();
    }

    return 0;
}

int Drivetrain::followLine(){
    if(sensors.onLine()){
        timeStamp = TimeNowMSec();
        drivePrimitive(60,40);
    }else{
        drivePrimitive(40, 60);
    }

    if(TimeNowMSec() - timeStamp > 400){
        return stop();
    }
}

int Drivetrain::driveUntilLine(){
    drivePrimitive(SPD, SPD);

    if(sensors.onLine()){
        timeStamp = 0;
        return stop();
    }

    return 0;
}

void Drivetrain::drivePrimitive(double lSpd, double rSpd){
    motorL.SetPercent(-1*(lSpd*LP + LK));
    motorR.SetPercent((rSpd*RP + RK));
}