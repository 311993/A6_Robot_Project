#include <sensor.h>

double Sensors::getRawColor(){
    return cds.Value();
}

int Sensors::isLight(){
    return cds.Value() < BLUE_THRESHOLD;
}

int Sensors::isRed(){
    return cds.Value() < RED_THRESHOLD;
}