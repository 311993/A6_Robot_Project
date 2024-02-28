#pragma once
#include <FEHIO.h>
#include <FEHBattery.h>
#include <FEHAccel.h>
#include <FEHBuzzer.h>
#include <FEHUtility.h>

using namespace std;

AnalogInputPin cds(FEHIO::P0_0);
const static double RED_THRESHOLD = 0.5, BLUE_THRESHOLD = 2.0;

class Sensors{
    public:
        static double getRawColor(){}
        static int isLight(){}
        static int isRed(){}

    private:
};