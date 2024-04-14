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
            substep += drivetrain.driveDistance(12.4); //12.5
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
            substep += drivetrain.turnLeft(202);
        break;

        case 2:
            substep += drivetrain.align();
        break;

        case 3:
            substep += drivetrain.driveDistance(8);
        break;

        case 4:
            substep += drivetrain.turnLeft(93);
        break;
        
        case 5:
            substep += drivetrain.driveBack(9.1 + leverNo * 4);
        break;

        case 6:
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
            substep++;
        break;

        case 1:
            substep ++;
        break;

        case 2:
            substep += drivetrain.driveDistance(3);
        break;

        case 3:
            substep += drivetrain.turnLeft(95);
        break;

        case 4:
            substep += drivetrain.driveDistance(27);
        break;

        case 5:
            substep += drivetrain.turnRight(100);
        break;

        case 6:
            substep += drivetrain.align();
        break;

        case 7:
            substep += drivetrain.driveDistance(19.25);
        break;

        case 8:
            drivetrain.drivePrimitive(-SPD,0);
            if(drivetrain.sensors.getBumpL()){
                drivetrain.stop();
                substep++;
            };
        break;

        case 9:
            substep += drivetrain.driveDistance(29);
        break;

        case 10:
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
            substep += drivetrain.driveBack(3.5);
        break;

        case 1:
            substep += drivetrain.turnRight(94);
        break;

        case 2:
            substep += drivetrain.driveDistance(2);
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
            substep ++;
        break;

        case 1:
            substep += drivetrain.turnRight(95);
        break;

        case 2:
            substep += drivetrain.driveDistance(15);
        break;

        case 3:
            substep += drivetrain.turnRight(95);
        break;

        case 4:
            substep += drivetrain.align();
        break;

        case 5:
            substep += drivetrain.driveDistance(3);
        break;

        case 6:
            substep += drivetrain.turnLeft(94);
        break;

        case 7:
            substep += drivetrain.driveUnbounded();
        break;

        case 8:
            drivetrain.stop();
            substep = 0;
            return 1;
        break;

    }

    return 0;
}