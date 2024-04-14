#include <sensor.h>

//Constructor: initialize robot components

Sensors::Sensors():
    cds(FEHIO::P0_0),
    bumpL(FEHIO::P3_0),
    bumpR(FEHIO::P3_7),
    bumpF(FEHIO::P3_5){}

//Get current CDS value
double Sensors::getRawColor(){
    return cds.Value();
}

//Get average CDS value
double Sensors::getAvgColor(){
    int sum = 0;

    for(int i = 0;  i < sizeof(colorSamples); i++){
        sum += colorSamples[i];
    }
    
    return sum/sizeof(colorSamples);
}

//Save current CDS value to storage
void Sensors::sampleColor(){
    
    for(int i = 1; i < sizeof(colorSamples); i++){
        colorSamples[i] = colorSamples[i - 1];
    }
    
    colorSamples[0] = getRawColor();
}

//Return whether CDS detects a light
int Sensors::isLight(){
    return cds.Value() < BLUE_THRESHOLD;
}

//Return whether CDS detects a RED light
int Sensors::isRed(){
    return cds.Value() < RED_THRESHOLD;
}

//Return whether back left bump switch is pressed
int Sensors::getBumpL(){
     return !bumpL.Value();
}

//Return whether back right bump switch is pressed
int Sensors::getBumpR(){
     return !bumpR.Value();
}

//Return whether arm bump switch is pressed
int Sensors::getBumpF(){

    return !bumpF.Value();
}