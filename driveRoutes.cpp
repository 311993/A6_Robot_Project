#include <main.h>

//Constructor: initialize control variables + set up subsystem dependencies
DriveRoutes::DriveRoutes(Drivetrain drivetrain):
    drivetrain(drivetrain),
    substep(0),
    subTimeStamp(0),
    color(0){}

//Subsequence for start button and luggage
int DriveRoutes::startToLuggage(){

    //Execute command based on robot substate,
    //Advance substate whenever a command is complete

    switch(substep){

        //Press start button
        case 0:
            substep += drivetrain.driveTime(-15, 2100); 
        break;

        //Move to luggage depot
        case 1:
            substep += drivetrain.driveDistance(12.4); //12.5
        break;

        case 2:
            substep += drivetrain.turnRight(45);
        break;

        case 3:
            substep += drivetrain.driveDistance(6); //14
        break;

        //Drop luggage
        case 4:
            substep += drivetrain.driveTime(100, 500);
        break;

        //End subsequence
        case 5:
            
            //Stop all motors + reset control vars
            drivetrain.stop();
            substep = 0;
           
            return 1; //Advance main state
        
        break;

    }

    return 0; //Maintain main state
}

//Subsequence for moving to levers based on lever number
int DriveRoutes::luggageToLevers(int leverNo){
    
    //Execute command based on robot substate,
    //Advance substate whenever a command is complete

    switch(substep){

        //Align with luggage depot
        case 0:
            substep += drivetrain.driveBack(9.75);
        break;

        case 1:
            substep += drivetrain.turnLeft(202);
        break;

        case 2:
            substep += drivetrain.align();
        break;

        //Move to levers
        case 3:
            substep += drivetrain.driveDistance(8);
        break;

        case 4:
            substep += drivetrain.turnLeft(93);
        break;
        
        case 5:
            substep += drivetrain.driveBack(9.1 + leverNo * 4);
        break;

        //End subsequence
        case 6:
            
            //Stop all motors + reset control vars
            drivetrain.stop();
            substep = 0;
           
            return 1; //Advance main state
        
        break;

    }

    return 0; //Maintain main state
}

//Subsequence for driving to kiosk + press kiosk button
int DriveRoutes::leversToKiosk(){

    //Execute command based on robot substate,
    //Advance substate whenever a command is complete

    switch(substep){
        
        //Move up ramp
        case 0:
            substep += drivetrain.driveDistance(3);
        break;

        case 1:
            substep += drivetrain.turnLeft(95);
        break;

        case 2:
            substep += drivetrain.driveDistance(27);
        break;

        //Align with wall
        case 3:
            substep += drivetrain.turnRight(100);
        break;

        case 4:
            substep += drivetrain.align();
        break;

        //Move to upper luggage depot
        case 5:
            substep += drivetrain.driveDistance(19.25);
        break;

        //Custom step: align left side using upper luggage depot
        case 6:

            //Static left turn
            drivetrain.drivePrimitive(-SPD,0);

            //Finish step if left bump switch is pressed
            if(drivetrain.sensors.getBumpL()){
                drivetrain.stop();
                substep++;
            };

        break;

        //Press button
        case 7:
            substep += drivetrain.driveDistance(29);
        break;

        //End subsequence
        case 8:
           
            //Stop all motors + reset control vars
            drivetrain.stop();
            substep = 0;
           
            return 1; //Advance main state
        
        break;

    }

    return 0; //Maintain main state
}

//Subsequence for moving in front of passport
int DriveRoutes::kioskToPassport(){

    //Execute command based on robot substate,
    //Advance substate whenever a command is complete

    switch(substep){

        //Move to passport
        case 0:
            substep += drivetrain.driveBack(3.5);
        break;

        case 1:
            substep += drivetrain.turnRight(94);
        break;

        case 2:
            substep += drivetrain.driveDistance(2);
        break;

        //End subsequence
        case 3:
            drivetrain.stop();
            substep = 0;
            return 1;
        break;

    }

    return 0;

}

//Subsequence for driving into final button
int DriveRoutes::passportToFinal(){
    
    //Execute command based on robot substate,
    //Advance substate whenever a command is complete

    switch(substep){
        
        //Move to right side wall
        case 0:
            substep += drivetrain.turnRight(95);
        break;

        case 1:
            substep += drivetrain.driveDistance(15);
        break;

        //Align with wall
        case 2:
            substep += drivetrain.turnRight(95);
        break;

        case 3:
            substep += drivetrain.align();
        break;

        //Move down ramp and drive into final button
        case 4:
            substep += drivetrain.driveDistance(3);
        break;

        case 5:
            substep += drivetrain.turnLeft(94);
        break;

        case 6:
            substep += drivetrain.driveUnbounded();
        break;

        //End subsequence
        case 7:
            
            //Stop all motors + reset control vars
            drivetrain.stop();
            substep = 0;
           
            return 1; //Advance main state
        
        break;

    }

    return 0; //Maintain main state
}