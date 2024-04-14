#include <main.h>

//Constructor: initialize control variables + set up subsystem dependencies
TaskSequences::TaskSequences(Drivetrain drivetrain, Arm arm):
    drivetrain(drivetrain),
    arm(arm),
    substep(0),
    subTimeStamp(0){}

//Subsequence for passport task
int TaskSequences::stampPassport(){

    //Execute command based on robot substate,
    //Advance substate whenever a command is complete

    switch(substep){

        //Position arm and move in for stamp
        case 0:
            substep += arm.setPos(120);
        break;

        case 1:
            substep += drivetrain.driveDistance(4);
        break;

        //Stamp passport
        case 2:
            substep += arm.reset();
        break;

        //Move out from passport + reset arm
        case 3:
            substep += arm.setPos(60);
        break;

        case 4:
            substep += drivetrain.driveBack(12);
        break;

        case 5:
            substep += arm.reset();
        break;

        //End subsequence
        case 6: 

            //Stop all motors + reset control vars
            drivetrain.stop();
            arm.stop();
            substep = 0;
           
            return 1; //Advance main state
        
        break;

    }

    return 0; //Maintain main state
}

//Subsequence for fuel lever task
int TaskSequences::fuelLever(int leverNo){

    //Execute command based on robot substate,
    //Advance substate whenever a command is complete

    switch(substep){

        //Flip lever down
        case 0:
            substep += arm.reset();
        break;

        case 1:
            substep += arm.setPos(140);
        break;

        //Drive back + position for flip up
        case 2:
            substep += arm.reset();
        break;

        case 3:
            substep += drivetrain.driveDistance(3);
        break;

        case 4:
            substep += arm.setPos(110);
        break;

        //Wait for bonus pts
        case 5:
            Sleep(5.0);
            substep++;
        break;

        //Flip lever up
        case 6:
            substep += drivetrain.driveBack(3.5);
        break;

        case 7:
            substep += arm.setPos(0);
        break;

        case 8:
            substep += arm.setPos(30);
        break;

        //Align with wall near levers + reset arm position
        case 9:
            substep += drivetrain.align();
        break;

        case 10:
            substep += arm.reset();
        break;

        //End subsequence
        case 11:
            
            //Stop all motors + reset control vars
            drivetrain.stop();
            arm.stop();
            substep = 0;
           
            return 1; //Advance main state
        
        break;

    }

    return 0; //Maintain main state
}