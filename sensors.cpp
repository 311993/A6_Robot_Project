#include <sensor.h>

Sensors::Sensors():
    cds(FEHIO::P0_0), 
    opto(FEHIO::P0_7),
    bumpL(FEHIO::P3_0),
    bumpR(FEHIO::P3_7),
    bumpF(FEHIO::P3_6){}

double Sensors::getRawColor(){
    return cds.Value();
}

double Sensors::getAvgColor(){
    int sum = 0;
    for(int i = 0;  i < sizeof(colorSamples); i++){
        sum += colorSamples[i];
    }
    return sum/sizeof(colorSamples);
}

void Sensors::sampleColor(){
    for(int i = 1; i < sizeof(colorSamples); i++){
        colorSamples[i] = colorSamples[i - 1];
    }
    colorSamples[0] = getRawColor();
}

int Sensors::isLight(){
    return cds.Value() < BLUE_THRESHOLD;
}

int Sensors::isRed(){
    return cds.Value() < RED_THRESHOLD;
}

int Sensors::onLine()
{
    return opto.Value() > LINE_THRESHOLD;
}

int Sensors::getBumpL()
{
     return !bumpL.Value();
}

int Sensors::getBumpR()
{
     return !bumpR.Value();
}

int Sensors::getBumpF(){

    return !bumpF.Value();
}
