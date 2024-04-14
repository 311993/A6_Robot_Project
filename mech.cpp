#include <mech.h>
#include <cmath>

//Constructor: initialize control variables + robot components
Arm::Arm(Sensors sensors):
    motorF(FEHMotor::Motor2, 7.2),
    sensors(sensors),
    angle(0),
    timeStamp(0){}

//Set arm to an angle from vertical
int Arm::setPos(double theta){
    
    //Record start time on first pass
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }
    
    //Move up/down to set angle
    liftPrimitive(theta > angle ? -LIFT_POW : LIFT_POW);

    //If the arm has moved the desired angle or hit the bump switch, finish the command
    if(TimeNowMSec() - timeStamp > abs(theta - angle)*DEGREES_TO_MSEC || (theta < angle && sensors.getBumpF())){
       
       //Reset control vars
       timeStamp = 0;
       angle = theta;

       return stop(); //Stop motor + finish command
    }

    return 0; //Continue command
}

//Stop the arm motor
int Arm::stop(){

    motorF.SetPercent(0);
    Sleep(100);
    
    return 1; //Finish command
}

//Set the arm back to vertical
int Arm::reset(){

    //Record start time on first pass
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    //Move up
    liftPrimitive(LIFT_POW);

    //If the arm reaches bump switch or times out, finish the command
    if(sensors.getBumpF() || (TimeNowMSec() - timeStamp) > 2000){
    
        //Reset control vars
        timeStamp = 0;
        angle = 0;

        return stop(); //Stop motor + finish command
    }

    return 0; //Continue command
}

//Set the arm motor to a percent power
void Arm::liftPrimitive(double pow){

    //Control for differences in battery power
    motorF.SetPercent(pow * MAX_VOLTAGE/Battery.Voltage());
}
