#include <main.h>

/*
55r
5
10l
30
90l
11
90r
28+
*/

DriveRoutes::DriveRoutes(Drivetrain drivetrain){
   this->drivetrain = drivetrain;
   substep = 0;
   subTimeStamp = 0;
}

int DriveRoutes::startToKiosk(){

    switch(substep){
        case 0:
            substep += drivetrain.turnRight(55);
        break;
        case 1:
            substep += drivetrain.driveDistance(5);
        break;
        case 2:
            substep += drivetrain.turnLeft(10);
        break;
        case 3:
            substep += drivetrain.driveDistance(30);
        break;
        case 4:
            substep += drivetrain.turnLeft(90);
        break;
        case 5:
            substep += drivetrain.driveDistance(11);
        break;
        case 6:
            substep += drivetrain.turnRight(80);
        break;
        case 7:
            substep += drivetrain.driveDistance(24);
        break;
    } 
    return (substep == 8) ? 2 : 1;
}