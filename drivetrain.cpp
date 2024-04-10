#include "drivetrain.h"
#include "FEHLCD.h"

Drivetrain::Drivetrain(Sensors sensors):
    motorL(FEHMotor::Motor0, 7.2),
    motorR(FEHMotor::Motor1, 7.2),
    encL(FEHIO::P1_0),
    encR(FEHIO::P2_0),
    sensors(sensors),
    timeStamp(0){}

void Drivetrain::printEncs(){
    LCD.Clear();
    LCD.WriteLine("L:");
    LCD.WriteLine(encL.Counts());
    LCD.WriteLine("");
    LCD.WriteLine("R:");
    LCD.WriteLine(encR.Counts());
}

int Drivetrain::stop(void){
    encL.ResetCounts();
    encR.ResetCounts();

    motorL.SetPercent(0);
    motorR.SetPercent(0);

    return 1;
}

int Drivetrain::breakTime(double mSec){
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    if(TimeNowMSec() - timeStamp > mSec){
       timeStamp = 0;
       return stop();
    }

    return 0;
}

int Drivetrain::breakEnc(double ticks){

    if((encL.Counts() + encR.Counts()/1.08)/2 > ticks){
       return stop();
    }

    return 0;
}

int Drivetrain::driveUnbounded(){
    drivePrimitive(SPD, SPD);

    return 0;
}

int Drivetrain::wait(double mSec){
    stop();

    return breakTime(mSec);
}

int Drivetrain::driveDistance(double dist){

    drivePrimitive(SPD, SPD);

    return useEnc ? breakEnc(dist*INCHES_TO_TICKS) : breakTime(dist*INCHES_TO_MSEC);
}

int Drivetrain::driveTime(double pow, int msec){

    drivePrimitive(pow, pow);

    return breakTime(msec);
}

int Drivetrain::drivePower(double pow, double dist){

    drivePrimitive(pow, pow);

    return breakEnc(dist*INCHES_TO_TICKS);
}

int Drivetrain::driveBack(double dist){

    drivePrimitive(-SPD, -SPD);

    return useEnc ? breakEnc(dist*INCHES_TO_TICKS) : breakTime(dist*INCHES_TO_MSEC);
}

int Drivetrain::turnLeft(double deg){

    drivePrimitive(-SPD, SPD);

    return useEnc ? breakEnc(deg*DEGREES_TO_TICKS * LTURNP) : breakTime(deg*DEGREES_TO_MSEC);
}

int Drivetrain::turnRight(double deg){

    drivePrimitive(SPD, -SPD);

    return useEnc ? breakEnc(deg*DEGREES_TO_TICKS) : breakTime(deg*DEGREES_TO_MSEC);
}

int Drivetrain::align(){
    drivePrimitive(-SPD, -SPD);

    if(sensors.getBumpL()){
       motorL.Stop();
    }

    if(sensors.getBumpR()){
        motorR.Stop();
    }

    if(sensors.getBumpL() && sensors.getBumpR()){
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
    motorL.SetPercent(-1*(lSpd*LP + LK)*(MAX_VOLTAGE/Battery.Voltage()));
    motorR.SetPercent((rSpd*RP + RK)*(MAX_VOLTAGE/Battery.Voltage()));
}