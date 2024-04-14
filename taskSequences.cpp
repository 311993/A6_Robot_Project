#include <main.h>

TaskSequences::TaskSequences(Drivetrain drivetrain, Arm forklift):
    drivetrain(drivetrain),
    forklift(forklift),
    substep(0),
    subTimeStamp(0){}

int TaskSequences::stampPassport(){
    switch(substep){

        case 0:
            substep += forklift.setPos(120);
        break;

        case 1:
            substep += drivetrain.driveDistance(4);
        break;

        case 2:
            substep += forklift.reset();
        break;

        case 3:
            substep += forklift.setPos(60);
        break;

        case 4:
            substep += drivetrain.driveBack(12);
        break;

        case 5:
            substep += forklift.reset();
        break;

        case 6:
            drivetrain.stop();
            forklift.stop();
            substep = 0;
            return 1;
        break;

    }

    return 0;
}

int TaskSequences::fuelLever(int leverNo){
    switch(substep){
        case 0:
            substep += forklift.reset();
        break;

        case 1:
            substep += forklift.setPos(140);
        break;

        case 2:
            substep += forklift.reset();
        break;

        case 3:
            substep += drivetrain.driveDistance(3);
        break;

        case 4:
            substep += forklift.setPos(110);
        break;

        case 5:
            Sleep(5.0);
            substep++;
        break;

        case 6:
            substep += drivetrain.driveBack(3.5);
        break;

        case 7:
            substep += forklift.setPos(0);
        break;

        case 8:
            substep += forklift.setPos(30);
        break;

        case 9:
            substep += drivetrain.align();
        break;

        case 10:
            substep += forklift.reset();
        break;

        case 11:
            drivetrain.stop();
            forklift.stop();
            substep = 0;
            return 1;
        break;

    }

    return 0;
}