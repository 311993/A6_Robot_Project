#include <main.h>

TaskSequences::TaskSequences(Drivetrain drivetrain, Arm forklift):
    drivetrain(drivetrain),
    forklift(forklift),
    substep(0),
    subTimeStamp(0){}

int TaskSequences::stampPassport(){
    switch(substep){

        case 0:
            substep += forklift.setPos(90);
        break;

        case 1:
            substep += drivetrain.driveDistance(3);
        break;

        case 2:
            substep += forklift.reset();
        break;

        case 3:
            drivetrain.stop();
            forklift.stop();
            return 1;
        break;

    }

    return 0;
}

int TaskSequences::fuelLever(int leverNo){
    switch(substep){
        case 0:
            substep += forklift.setPos(90);
        break;

        case 1:
            substep += drivetrain.driveBack(3);
        break;

        case 2:
            substep += forklift.reset();
        break;

        case 3:
            //Sleep(5.0);
            substep++;
        break;

        case 4:
            substep += drivetrain.driveDistance(3);
        break;

        case 5:
            substep += forklift.setPos(0);
        break;

        case 6:
            substep += drivetrain.driveDistance(10.5 - 4 * leverNo);
        break;

        case 7:
            substep += forklift.reset();
        break;

        case 8:
            drivetrain.stop();
            forklift.stop();
            return 1;
        break;

    }

    return 0;
}