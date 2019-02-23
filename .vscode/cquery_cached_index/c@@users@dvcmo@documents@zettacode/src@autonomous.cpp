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
  if (mainAuton == 5) {
    flip(90); // Puts claw down
    drive(38, 150); // drive to claw
    flip(45, 50); // picks up cap
    drive(-38, 150); // moves back
    turn(-90 * red, 150); // turns to face north
    drive(36, 100); // drive to post
    turn(-90 * red, 100); // turn to face post
    lift(3, true); // lift to high position
    drive(10, 100); // drive a little bit foward with lift up toward post
    flip(90, 25); // puts cap down
  }

  if (mainAuton == 6) {
    intakeActive(true); // turns on intake
    drive(38, -150); // drive to cap
    pros::delay(250); // give some time for intake to work
    intakeActive(false); // turns off intake
    drive(34, 150); // drive back
    turn(-90 * red, 100); // turn towards flags
    drive(-36, 150); // slam bottom flag
  }

  if (mainAuton == 7) {
    intakeActive(true); // turns on intake
    drive(38, -150); // drive to cap
    pros::delay(250); // give some time for intake to work
    intakeActive(false); // turns off intake
    drive(34, 150); // drive back
    turn(-90 * red, 100); // turn towards flags
    drive(-36, 150); // slam bottom flag
    // perform auton 6
    drive(12, 100); // drive to line up with a cap
    turn(-90 * red, 100); // turn to face cap
    flip(90); // dicks out for harambe
    drive(30, 150);
    flip(); // flips cap
  }

  if (mainAuton == 8) {
    intakeActive(true); // turns on intake
    drive(38, -150); // drive to cap
    pros::delay(250); // give some time for intake to work
    intakeActive(false); // turns off intake
    drive(34, 150); // drive back
    turn(-90 * red, 100); // turn towards flags
    drive(-36, 150); // slam bottom flag
    // performs auton 6
    drive(84, 150); // drive to line up with platform
    turn(90, 100); // face platform
    drive(48, 200); // get on the platform you fat fuck
  }

  if (mainAuton == 9) {
    flip(90); // Puts claw down
    drive(40, 150); // drive to cap not too far pls
    flip(45, 25); // picks up cap
    pros::delay(1000); // slow down you fuck
    drive(-22, 150); // moves back
    turn(90 * red, 150); // turns to face south
    drive(2, 100); // drive to post
    turn(90 * red, 100); // turn to face post
    lift(2, true); // lift to middle  position
    drive(4, 100); // drive foward a bit
    lift(0, false);
    flip(90, 100); // puts cap down
  }
  //---------------------//
}
const char * autonDescription(int i){
	std::string description = "No Autonumous"; //-0-//
  if(i==1){   description = "FLG - Middle & Bottom flag; Top from middle post";} //-1-//
  if(i==2){   description = "FLG - Middle post all 3 flags";} //-2-//
  if(i==3){   description = "empty";} //-3-//
  if(i==4){   description = "Unfinished Autonomous";} //-4-//
  if(i==5){   description = "Far side auton UNTESTED";} //-5-//
  if(i==6){   description = "Flag side auton, no add-ons UNTESTED";} //-6-//
  if(i==7){   description = "Flag side auton, Add on: Flip cap UNTESTED";} //-7-//
  if(i==8){   description = "Flag side auton, Add on: park UNTESTED";} //-8-//
  if(i==9){   description = "Far side auton but ONLY IF we have alliance auton";} //-9-//
  if(i==10){  description = "empty";} //-10-//
  if(i==11){  description = "empty";} //-11-//
  if(i==12){  description = "empty";} //-12-//

	return description.c_str();
}
