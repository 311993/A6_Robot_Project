#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHAccel.h>
#include <FEHBattery.h>
#include <FEHBuzzer.h>
#include <FEHRPS.h>
#include <FEHSD.h>
#include <string.h>
#include <stdio.h>

//AnalogInputPin cds = AnalogInputPin(FEHIO::P0_0);
//FEHServo servo = FEHServo(FEHServo::Servo0);

DigitalInputPin switchFR(FEHIO::P0_0);
DigitalInputPin switchFL(FEHIO::P0_1);
DigitalInputPin switchBR(FEHIO::P0_2);
DigitalInputPin switchBL(FEHIO::P2_7);

FEHMotor rightMotor(FEHMotor::Motor0, 9.0);
FEHMotor leftMotor(FEHMotor::Motor1, 9.0);

void forward();
void backward();
void turnLeft();
void turnRight();
void stop();

int main(void){
    /*Part 1:
    int *x,*y;
    
    while(true){
        LCD.Clear();
        LCD.WriteLine(cds.Value());
        Sleep(50);
    }*/

    /*Part 2: 
    servo.SetMin(510);
    servo.SetMax(2365);

    while(true){
        servo.SetDegree(180.0/3.4 * cds.Value());
    }
    */

    /*Part 3: */
    int x = 0, y = 0;
    
    while(!LCD.Touch(&x,&y)){}
    
    while(switchFL.Value()){
        forward();
    }
    stop();

    while(switchBR.Value()){
        turnRight();
    }
    stop();

    while(switchBR.Value() || switchBL.Value()){
        backward();
    }
    stop();

    while(switchFL.Value() || switchFR.Value()){
        forward();
    }
    stop();

    while(switchBL.Value()){
        turnLeft();
    }
    stop();

    while(switchBR.Value() || switchBL.Value()){
        backward();
    }
    stop();

    while(switchFL.Value() || switchFR.Value()){
        forward();
    }
    stop();

    return 0;
}

void forward(){
    leftMotor.SetPercent(25);
    rightMotor.SetPercent(-25);
}

void backward(){
    leftMotor.SetPercent(-25);
    rightMotor.SetPercent(25);
}

void stop(){
    leftMotor.SetPercent(0);
    rightMotor.SetPercent(0);
    Sleep(1.0);
}

void turnLeft(){
    leftMotor.SetPercent(-25);
    rightMotor.SetPercent(0);
}

void turnRight(){
    leftMotor.SetPercent(0);
    rightMotor.SetPercent(25);
}