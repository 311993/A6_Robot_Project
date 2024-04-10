#include <main.h>

DriveRoutes::DriveRoutes(Drivetrain drivetrain):
    drivetrain(drivetrain),
    substep(0),
    subTimeStamp(0),
    color(0){}

int DriveRoutes::startToLuggage(){
    switch(substep){
        case 0:
            substep += drivetrain.driveTime(-15, 2100); 
        break;

        case 1:
            substep += drivetrain.driveDistance(11.5); //12.5
        break;

        case 2:
            substep += drivetrain.turnRight(45);
        break;

        case 3:
            substep += drivetrain.driveDistance(6); //14
        break;

        case 4:
            substep += drivetrain.driveTime(100, 500);
        break;

        case 5:
            drivetrain.stop();
            substep = 0;
            return 1;
        break;

    }

    return 0;
}

int DriveRoutes::luggageToLevers(int leverNo){
    
    switch(substep){
        case 0:
            substep += drivetrain.driveBack(9.75);
        break;

        case 1:
            substep += drivetrain.turnRight(90);
        break;

        case 2:
            substep += drivetrain.driveDistance(11.5 + leverNo * 4);
        break;

        case 3:
            drivetrain.stop();
            substep = 0;
            return 1;
        break;

    }

    return 0;
}

int DriveRoutes::leversToKiosk(){

     switch(substep){
        case 0:
            substep += drivetrain.turnRight(180);
        break;

        case 1:
            substep += drivetrain.align();
        break;

        case 2:
            substep += drivetrain.driveDistance(4);
        break;

        case 3:
            substep += drivetrain.turnLeft(95);
        break;

        case 4:
            substep += drivetrain.driveDistance(12);
        break;

        case 5:
            substep += drivetrain.turnLeft(90);
        break;

        case 6:
            substep += drivetrain.align();
        break;

        case 7:
            substep += drivetrain.driveDistance(12);
        break;

        case 8:
            substep += drivetrain.turnLeft(90);
        break;

        case 9:
            substep += drivetrain.align();
        break;

        case 10:
            substep += drivetrain.driveDistance(18);
        break;

        case 11:
            drivetrain.stop();
            substep = 0;
            return 1;
        break;

    }

    return 0;
}

int DriveRoutes::kioskToPassport(){

    switch(substep){
        case 0:
            substep += drivetrain.driveBack(6);
        break;

        case 1:
            substep += drivetrain.turnRight(90);
        break;

        case 2:
            substep += drivetrain.driveDistance(9);
        break;

        case 3:
            drivetrain.stop();
            substep = 0;
            return 1;
        break;

    }

    return 0;

}

int DriveRoutes::passportToFinal(){
    
    switch(substep){
        case 0:
            substep += drivetrain.driveBack(6);
        break;

        case 1:
            substep += drivetrain.turnRight(90);
        break;

        case 2:
            substep += drivetrain.driveDistance(12);
        break;

        case 3:
            substep += drivetrain.turnRight(90);
        break;

        case 4:
            substep += drivetrain.align();
        break;

        case 5:
            substep += drivetrain.turnRight(90);
        break;

        case 6:
            substep += drivetrain.driveDistance(4);
        break;

        case 7:
            substep += drivetrain.turnLeft(90);
        break;

        case 8:
            substep += drivetrain.driveUnbounded();
        break;

        case 9:
            drivetrain.stop();
            substep = 0;
            return 1;
        break;

    }

    return 0;
}