#include <forklift.h>

Forklift::Forklift(Sensors sensors):
    lift(FEHMotor::Motor2, 7.2),
    sensors(sensors),
    timeStamp(0){}

int Forklift::stop(){
    lift.SetPercent(0);

    return 1;
}

int Forklift::botToTop(){
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

int Forklift::topToBot(){
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    liftPrimitive(LIFT_POW);

    if(TimeNowMSec() - timeStamp > MSEC_TOP_TO_BOT){
       timeStamp = 0;
       return stop();
    }

    return 0;
}

int Forklift::topToMid(){
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    liftPrimitive(LIFT_POW);

    if(TimeNowMSec() - timeStamp > MSEC_TOP_TO_MID){
       timeStamp = 0;
       return stop();
    }

    return 0;
}

int Forklift::botToMid(){
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

int Forklift::midToTop(){
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

int Forklift::midToBot(){
    if(timeStamp == 0){
        timeStamp = TimeNowMSec();
    }

    liftPrimitive(LIFT_POW);

    if(TimeNowMSec() - timeStamp > MSEC_MID_TO_BOT){
       timeStamp = 0;
       return stop();
    }

    return 0;
}

int Forklift::hold(bool hasLug){
    liftPrimitive(hasLug ? FF_POW_LUG : FF_POW);
}

void Forklift::liftPrimitive(double pow){
    lift.SetPercent(pow * MAX_VOLTAGE/Battery.Voltage());
}
