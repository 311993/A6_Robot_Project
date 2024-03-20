#include <main.h>

TaskSequences::TaskSequences(Drivetrain drivetrain, Forklift forklift):
    drivetrain(drivetrain),
    forklift(forklift),
    substep(0),
    subTimeStamp(0){}

int TaskSequences::fuelLever(){
    switch(substep){
        case 0:
            substep += forklift.botToTop();
        break;

        case 1:
            substep += drivetrain.driveDistance(3);
            forklift.hold(0);
        break;

        case 2:
            substep += forklift.topToMid();
        break;

        case 3:
            substep += drivetrain.driveBack(3);
        break;

        case 4:
            substep += forklift.midToBot();
        break;

        case 5:
            Sleep(6.0);
            substep ++;
        break;

        case 6:
            substep += drivetrain.driveDistance(3);
        break;

        case 7:
            substep += forklift.botToMid();
        break;

        case 8:
            drivetrain.stop();
            return 3;
        break;

    }

    return 2;
}