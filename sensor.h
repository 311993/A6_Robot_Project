#pragma once
#include <FEHIO.h>
#include <FEHBattery.h>
#include <FEHAccel.h>
#include <FEHBuzzer.h>
#include <FEHUtility.h>

using namespace std;

const static double RED_THRESHOLD = 0.5, BLUE_THRESHOLD = 2.0;

class Sensors{
    public:
        explicit Sensors();
        double getRawColor();
        double getAvgColor();
        void sampleColor();

        int isLight();
        int isRed();

    private:
        double colorSamples[5];
        AnalogInputPin cds;
};