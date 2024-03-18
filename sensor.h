#pragma once
#include <FEHIO.h>
#include <FEHBattery.h>
#include <FEHAccel.h>
#include <FEHBuzzer.h>
#include <FEHUtility.h>

using namespace std;

#define RED_THRESHOLD 0.6
#define BLUE_THRESHOLD 1.0
#define LINE_THRESHOLD 2.0

class Sensors{
    public:
        explicit Sensors();

        double getRawColor();
        double getAvgColor();
        void sampleColor();

        int isLight();
        int isRed();

        int onLine();
        int getBump();

    private:
        double colorSamples[5];
        AnalogInputPin cds;
        AnalogInputPin opto;
        DigitalInputPin bump;
};