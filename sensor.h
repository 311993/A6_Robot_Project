#pragma once
#include <FEHIO.h>
#include <FEHBattery.h>
#include <FEHAccel.h>
#include <FEHBuzzer.h>
#include <FEHUtility.h>

using namespace std;

//Define constants
#define RED_THRESHOLD 0.6 //Max value for red light
#define BLUE_THRESHOLD 1.0 //Max value for blue light

class Sensors{
    public:
        explicit Sensors(); //Constructor

        //CDS cell methods
        double getRawColor();
        double getAvgColor();
        void sampleColor();
        int isLight();
        int isRed();

        //Bump switch methods
        int getBumpL();
        int getBumpR();
        int getBumpF();

    private:

        double colorSamples[5]; //Color sample storage for averaging

        //Required components
        AnalogInputPin cds;
        DigitalInputPin bumpL;
        DigitalInputPin bumpR;
        DigitalInputPin bumpF;
};