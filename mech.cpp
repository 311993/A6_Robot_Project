#include <mech.h>
#include <cmath>

Arm::Arm(Sensors sensors):
    motorF(FEHMotor::Motor2, 7.2),
    sensors(sensors),
    angle(0),
    timeStamp(0){}

int Arm::setPos(double theta){
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    liftPrimitive(theta > angle ? -LIFT_POW : LIFT_POW);

    if(TimeNowMSec() - timeStamp > abs(theta - angle)*DEGREES_TO_MSEC || (theta < angle && sensors.getBumpF())){
       timeStamp = 0;
       angle = theta;
       return stop();
    }

    return 0;
}

int Arm::stop(){
    motorF.SetPercent(0);
    Sleep(100);
    return 1;
}

int Arm::reset(){

    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    liftPrimitive(LIFT_POW);

    if(sensors.getBumpF() || (TimeNowMSec() - timeStamp) > 2000){
        angle = 0;
        timeStamp = 0;
        return stop();
    }

    return 0;
}

int Arm::botToTop(){
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    liftPrimitive(LIFT_POW);

    if(TimeNowMSec() - timeStamp > MSEC_BOT_TO_TOP){
       timeStamp = 0;
       return stop();
    }

    return 0;
}

int Arm::topToBot(){
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    liftPrimitive(-LIFT_POW);

    if(TimeNowMSec() - timeStamp > MSEC_TOP_TO_BOT){
       timeStamp = 0;
       return stop();
    }

    return 0;
}

int Arm::topToMid(){
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    liftPrimitive(-LIFT_POW);

    if(TimeNowMSec() - timeStamp > MSEC_TOP_TO_MID){
       timeStamp = 0;
       return stop();
    }

    return 0;
}

int Arm::botToMid(){
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    liftPrimitive(LIFT_POW);

    if(TimeNowMSec() - timeStamp > MSEC_BOT_TO_MID){
       timeStamp = 0;
       return stop();
    }

    return 0;
}

int Arm::midToTop(){
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    liftPrimitive(LIFT_POW);

    if(TimeNowMSec() - timeStamp > MSEC_MID_TO_TOP){
       timeStamp = 0;
       return stop();
    }

    return 0;
}

int Arm::midToBot(){
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    liftPrimitive(-LIFT_POW);

    if(TimeNowMSec() - timeStamp > MSEC_MID_TO_BOT){
       timeStamp = 0;
       return stop();
    }

    return 0;
}

int Arm::hold(bool hasLug){
    liftPrimitive(hasLug ? FF_POW_LUG : FF_POW);
}

void Arm::liftPrimitive(double pow){
    motorF.SetPercent(pow * MAX_VOLTAGE/Battery.Voltage());
}
