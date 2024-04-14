#include "drivetrain.h"
#include "FEHLCD.h"

//Constructor: initialize control variables + robot components
Drivetrain::Drivetrain(Sensors sensors):
    motorL(FEHMotor::Motor0, 7.2),
    motorR(FEHMotor::Motor1, 7.2),
    encL(FEHIO::P1_0),
    encR(FEHIO::P2_0),
    sensors(sensors),
    timeStamp(0){}

//Display encoder counts on screen
void Drivetrain::printEncs(){
    LCD.Clear();
    LCD.WriteLine("L:");
    LCD.WriteLine(encL.Counts());
    LCD.WriteLine("");
    LCD.WriteLine("R:");
    LCD.WriteLine(encR.Counts());
}

//Stop motors + reset encoders
int Drivetrain::stop(void){

    encL.ResetCounts();
    encR.ResetCounts();

    motorL.SetPercent(0);
    motorR.SetPercent(0);

    Sleep(20);

    return 1; //Finish command
}

//Return whether or not to finish command based on time
int Drivetrain::breakTime(double mSec){

    //Record start time on first pass
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    //Timeout -> finish command + reset time control
    if(TimeNowMSec() - timeStamp > mSec){

       timeStamp = 0;
       return stop(); //Finish command
    }

    return 0; //Continue command
}

//Return whether or not to finish command based on encoder ticks
int Drivetrain::breakEnc(double ticks){

    //Finsh if desired ticks are reached
    if((encL.Counts() + encR.Counts()/1.08)/2 > ticks){

       return stop(); //Finish command
    }

    return 0; //Continue command
}

//Drive forward forever
int Drivetrain::driveUnbounded(){
    drivePrimitive(SPD, SPD);

    return 0;
}

//Wait for a specified time
int Drivetrain::wait(double mSec){
    stop();

    return breakTime(mSec);
}

//Drive forward a distance
int Drivetrain::driveDistance(double dist){

    drivePrimitive(SPD, SPD);

    return useEnc ? breakEnc(dist*INCHES_TO_TICKS) : breakTime(dist*INCHES_TO_MSEC);
}

//Drive back a distance
int Drivetrain::driveBack(double dist){

    drivePrimitive(-SPD, -SPD);

    return useEnc ? breakEnc(dist*INCHES_TO_TICKS) : breakTime(dist*INCHES_TO_MSEC);
}

//Turn left a number of degrees
int Drivetrain::turnLeft(double deg){

    drivePrimitive(-SPD, SPD);

    return useEnc ? breakEnc(deg*DEGREES_TO_TICKS_L) : breakTime(deg*DEGREES_TO_MSEC);
}

//Turn right a number of degrees
int Drivetrain::turnRight(double deg){

    drivePrimitive(SPD, -SPD);

    return useEnc ? breakEnc(deg*DEGREES_TO_TICKS_R) : breakTime(deg*DEGREES_TO_MSEC);
}

//Drive forward an amount of time at a specified power
int Drivetrain::driveTime(double pow, int msec){

    drivePrimitive(pow, pow);

    return breakTime(msec);
}

//Align with the wall behind
int Drivetrain::align(){

    //Back up
    drivePrimitive(-20, -20);

    //if only one bump switch is hit, shut off that side drive and speed up other to finish aligning
    if(sensors.getBumpL()){
       drivePrimitive(0, -50);
    }

    if(sensors.getBumpR()){
        drivePrimitive(-50, 0);
    }

    //Both bump switches are pressed -> aligned
    if(sensors.getBumpL() && sensors.getBumpR()){

        timeStamp = 0; //Reset time control
        return stop(); //Finish command
    }

    return 0; //Continue command
}

//Drive left and right side wheels at specified percent powers
void Drivetrain::drivePrimitive(double lSpd, double rSpd){

    //Control for battery power changes + use PK control
    motorL.SetPercent(-1*(lSpd*LP + LK)*(MAX_VOLTAGE/Battery.Voltage()));
    motorR.SetPercent((rSpd*RP + RK)*(MAX_VOLTAGE/Battery.Voltage()));
}