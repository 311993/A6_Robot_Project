#include "drivetrain.h"

int Drivetrain::stop(void){
    motorL.SetPercent(0);
    motorR.SetPercent(0);

    return 1;
}

int Drivetrain::driveUnbounded(double spd){
    drivePrimitive(spd, spd);

    return 0;
}

int Drivetrain::driveDistance(double dist, double spd){
    drivePrimitive(spd, spd);

    if(TimeNowMSec() - timeStamp > dist*INCHES_TO_MSEC){
       return stop(); 
    }

    return 0;
}

int Drivetrain::turnLeft(double deg, double spd){
    drivePrimitive(-spd, spd);

    if(TimeNowMSec() - timeStamp > deg*DEGREES_TO_MSEC){
       return stop(); 
    }

    return 0;
}

int Drivetrain::turnRight(double deg, double spd){
    turnLeft(deg, -spd);
}

void Drivetrain::drivePrimitive(double lSpd, double rSpd){
    motorL.SetPercent(lSpd*LP + LK);
    motorL.SetPercent(-1*(rSpd*RP + RK));
}