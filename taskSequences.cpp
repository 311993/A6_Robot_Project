#include <main.h>

TaskSequences::TaskSequences(Drivetrain drivetrain, Forklift forklift):
    drivetrain(drivetrain),
    forklift(forklift),
    substep(0),
    subTimeStamp(0){}

int TaskSequences::stampPassport(){
    switch(substep){
        case 0:
            substep += drivetrain.driveDistance(8);
        break;

        case 1:
            substep += drivetrain.turnLeft(70);
        break;

        case 2:
            substep += drivetrain.driveDistance(6);
        break;

        case 3:
            substep += drivetrain.turnRight(80);
        break;

        case 4:
            substep += drivetrain.driveDistance(9);
        break;

        case 5:
            substep += drivetrain.turnRight(70);
        break;

        case 6:
            substep += drivetrain.driveDistance(6);
        break;

        case 7:
            substep += forklift.botToTop();
        break;

        case 8:
            substep += forklift.topToBot();
        break;

        case 9:
            substep += drivetrain.driveBack(5);
        break;

        case 10:
            drivetrain.stop();
            forklift.stop();
            return 3;
        break;

    }

    return 2;
}

int TaskSequences::fuelLever(){
    switch(substep){
        case 0:
            substep += forklift.botToTop();
        break;

        case 1:
            substep += drivetrain.driveDistance(3.5);
            forklift.hold(0);
        break;

        case 2:
            substep += forklift.topToMid();
        break;

        case 3:
            substep += drivetrain.driveBack(3.5);
        break;

        case 4:
            substep += forklift.midToBot();
        break;

        case 5:
            Sleep(6.0);
            substep ++;
        break;

        case 6:
            substep += drivetrain.driveDistance(3.5);
        break;

        case 7:
            substep += forklift.botToTop();
        break;

        case 8:
            substep += drivetrain.driveBack(3.5);
        break;

        case 9:
            substep += forklift.topToBot();
        break;

        case 10:
            drivetrain.stop();
            forklift.stop();
            return 3;
        break;

    }

    return 2;
}