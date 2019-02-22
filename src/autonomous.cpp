#include "main.h"
#include "MyHeaders/globalVariables.h"
#include "MyHeaders/autonMethods.h"

void autonomous() {
  int red = 2*redTeam-1;
  //---------------------//
  if(mainAuton==0){//If No autonomous is selected
    shoot(100);
  }
  if(mainAuton==1){
    shoot(shotA2);
    turn(-15*red,200);
    drive(-48,200);
    drive(48,200);
    turn(90*red,200);
    intakeActive(true);
    drive(-43,200);
    turn(-70*red,200);
    indexUntil();
    shoot(shotA);
  }
  if(mainAuton==2){
    intakeActive(true);
    drive(-43,200);
    drive(45,200);
    turn(-80,200);
    shoot(shotA);
    indexUntil();
    shoot(shotA2);
    turn(-5,100);
    drive(-28,200);
  }
  if(mainAuton==3){
    intakeActive(true);
    drive(-43,200);
    intakeActive(false);
    turn(-90*red, 100);
    shoot(shotB);
    indexUntil();
    shoot(shotB2);
  }
  if(mainAuton==4){
    flip(90);
    lift(0, true);
    drive(43,200);
    flip(45,50);
    turn(90, 100);
    drive(30,100);

  }
  //---------------------//
}
const char * autonDescription(int i){
	std::string description = "No Autonumous"; //-0-//
  if(i==1){   description = "FLG - Middle & Bottom flag; Top from middle post";} //-1-//
  if(i==2){   description = "FLG - Middle post all 3 flags";} //-2-//
  if(i==3){   description = "empty";} //-3-//
  if(i==4){   description = "CAPPIe";} //-4-//
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
