#include <sensor.h>

Sensors::Sensors():cds(FEHIO::P0_0){}

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