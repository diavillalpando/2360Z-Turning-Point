#include "main.h"
#include "MyHeaders/globalVariables.h"
#include "MyHeaders/autonMethods.h"

pros::Motor aimer(anglePort);
pros::Motor arm(armPort,true);

int loops = 0;
/*------------------------------------------------------------------------------------------------
| --API--
|   - drive(int inches,int speed) [Making the robot drive forwards/backwards]
|       - inches: the amount of inches the robot will drive
|       - speed: the rpm the wheels will rotate in
|
|   - turn(int degrees,int speed) [Making the robot turn]
|       - degrees: the degrees, clockwise, the robot will turn
|       - speed: the rpm the wheels will rotate in
|
|   - aimTick(int ticks, bool wait) [Making the puncher angle]
|       - ticks: the amount of ticks the aimer motor will go to
|       - wait: whether or not the code will halt until it finishes aiming
|
|   - shoot() [Shooting a ball]
|
|   - intakeActive(int direction) [controlling the intake]
|       - direction: wether it will intake or push them out
|           - 0 will disable it, >0 will intake, <0 will reverse
|
|   - armPos(int level, bool wait)  [controlling the multi-tool]
|       - level: the position the arm will go to
|           - 0 = stored, 1 = carry, 2 = place
|
------------------------------------------------------------------------------------------------*/


void autonomous() {
  int red = 2*redTeam-1; //use this variable and multiply it with your turn degrees
  //---------------------//


  if(mainAuton==1){//If No autonomous is selected
    armPos(1, false);
    aimTick(shotA, true);
    shoot();
    armPos(0, false);
    turn(-10,50);
    intakeActive(1);
    aimTick(shotA2, false);
    drive(50,200);
    drive(-50,200);
    shoot();
    turn(70,50);
    intakeActive(1);
    drive(45,200);
    drive(-45,200);
    turn(-80,50);
    shoot();
  }

  if(mainAuton==0){//If No autonomous is selected
    intakeActive(1);
    drive(38,200);
    pros::delay(100);
    intakeActive(0);
    drive(-38, 200);
    turn(-90 * red, 140);
    intakeActive(-1);
    pros::delay(280);
    intakeActive(0);
    for(int i = 0; i < 100; i++)
    {
      double where = findFlag(0,false);
      pros::delay(10);
    }
    armPos(1,false);
    double where = findFlag(1,false);
    while (where==0)
    {
      double where = findFlag(1,false);
      pros::delay(10);
      loops++;
      if (loops >= 150)
      {
        drive(0,0);
        break;
      }
    }
    shoot();
    aimTick(shotA, true);
    intakeActive(1);
    pros::delay(500);
    intakeActive(0);
    shoot();
    pros::delay(100);
    //pros::delay(100); b
    drive(47,200);
    //pros::delay(100);
    drive(-50,200);
  }


  //---------------------//
}
const char * autonDescription(int i){
	std::string description = "No Autonumous"; //-0-//
  if(i==1){   description = "big gei lol";} //-1-//
  if(i==2){   description = "empty";} //-2-//
  if(i==3){   description = "empty";} //-3-//
  if(i==4){   description = "empty";} //-4-//
  if(i==5){   description = "empty";} //-5-//
  if(i==6){   description = "empty";} //-6-//
  if(i==7){   description = "empty";} //-7-//
  if(i==8){   description = "empty";} //-8-//
  if(i==9){   description = "empty";} //-9-//
  if(i==10){  description = "empty";} //-10-//
  if(i==11){  description = "empty";} //-11-//
  if(i==12){  description = "empty";} //-12-//

	return description.c_str();
}

// 05/01/2019
