#include <main.h>

DriveRoutes::DriveRoutes(Drivetrain drivetrain):
    drivetrain(drivetrain),
    substep(0),
    subTimeStamp(0),
    color(0){}

int DriveRoutes::startToLevers(int leverNo){
    switch(substep){
        case 0:
            substep += drivetrain.driveDistance(12);
        break;

        case 1:
            substep += drivetrain.turnLeft(45);
        break;

        case 2:
            substep += drivetrain.driveDistance(6 + leverNo * 4);
        break;

        case 3:
            substep += drivetrain.turnLeft(90);
            return 2;
        break;

    }

    return 1;
}

int DriveRoutes::lightToKiosk(){
    switch(substep){
        case 0:
            substep += drivetrain.driveBack(10 + color*6);
        break;
        case 1:
            substep += drivetrain.turnRight(43);
        break;
        case 2:
            substep += drivetrain.driveDistance(12 + 6*color);
        break;
        case 3:
            substep = 0;
            return 4;
        break;
    }

    return 3;
}

int DriveRoutes::upperToLight(){

    switch(substep){
        case 0:
            substep += drivetrain.turnLeft(48);
        break;
        case 1:
            substep += drivetrain.driveDistance(27);
        break;
        case 2:
            LCD.SetBackgroundColor(color ? LCD.Red : LCD.Blue);
            LCD.Clear();
            substep = 0;
            return 3;
        break;
    }

    return 2;
}

int DriveRoutes::findLight(){

    switch(substep){
        case 0:
            substep += drivetrain.turnLeft(90);
        break;
        case 1:
            substep += drivetrain.driveDistance(30);
        break;
        case 2:
            substep += drivetrain.driveUntilLine();
        break;
        case 3:
            substep += drivetrain.turnRight(60);
        break;
        case 4:
            substep += drivetrain.followLine();
        break;
        case 5:
            substep +=  drivetrain.turnRight(0);
        break;
        case 6:
            substep += drivetrain.driveDistance(0);
        break;
        case 7:
            LCD.WriteLine(color ? "red" : "blue");
            substep = 0;
            return 3;
        break;
    }

    return 2;
}

int DriveRoutes::startToUpper(){
    
    switch(substep){
        case 0:
            substep += drivetrain.turnRight(55);
        break;
        case 1:
            substep += drivetrain.driveDistance(5);
        break;
        case 2:
            substep += drivetrain.turnLeft(17);
        break;
        case 3:
            substep += drivetrain.driveDistance(30);
        break;
    }

    if(substep == 4){
        substep = 0;
        return 2;
    }

    return 1;
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
            substep += drivetrain.turnLeft(12);
        break;
        case 3:
            substep += drivetrain.driveDistance(30);
        break;
        case 4:
            substep += drivetrain.turnLeft(90);
        break;
        case 5:
            substep += drivetrain.driveDistance(9);
        break;
        case 6:
            substep += drivetrain.turnRight(100);
        break;
        case 7:
            substep += drivetrain.driveDistance(20);
        break;
    }

    if(substep == 8){
        substep = 0;
        return 2;
    }

    return 1;
}

int DriveRoutes::kioskToStart(){

    switch(substep){
        case 7:
            substep ++;//= drivetrain.turnLeft(55);
        break;
        case 6:
            substep += drivetrain.driveDistance(5);
        break;
        case 5:
            substep += drivetrain.turnLeft(10);
        break;
        case 4:
            substep += drivetrain.driveDistance(30);
        break;
        case 3:
            substep += drivetrain.turnRight(70);
        break;
        case 2:
            substep += drivetrain.driveDistance(13 - 5*color);
        break;
        case 1:
            substep += drivetrain.turnRight(90);
        break;
        case 0:
            substep += drivetrain.driveBack(20);
        break;
    }

    return (substep == 8) ? 5 : 4;
}