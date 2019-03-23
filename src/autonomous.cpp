#include "main.h"
#include "MyHeaders/globalVariables.h"
#include "MyHeaders/autonMethods.h"

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
  if(mainAuton==0){//If No autonomous is selected
    drive(48, 200);
    drive(-48,200);
  }
  //---------------------//
}
const char * autonDescription(int i){
	std::string description = "No Autonumous"; //-0-//
  if(i==1){   description = "empty";} //-1-//
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
