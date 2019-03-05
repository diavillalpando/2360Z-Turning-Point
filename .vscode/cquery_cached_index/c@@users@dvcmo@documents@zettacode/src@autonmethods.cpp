#include "main.h"
#include "MyHeaders/globalVariables.h"

/*------------------------------------------------------------------------------------------------
| --Drive Method--
|   - Moves the robot a certain amount of inches[if Inches is negative it will drive backwards]
------------------------------------------------------------------------------------------------*/
void drive(int inches, int speed){
  pros::Motor left_mtr(leftPort);
	pros::Motor left_mtr2(leftPort2,true);
	pros::Motor right_mtr(rightPort,true);
	pros::Motor right_mtr2(rightPort2);

  left_mtr.move_velocity(0);
  left_mtr2.move_velocity(0);
  right_mtr.move_velocity(0);
  right_mtr2.move_velocity(0);

  int direction = 2*(inches>0)-1;
  double rotations = inches/(wheelDiameter*pi);
  double ma = 1.5;
  double encoderUnits = rotations*900*ma;

  left_mtr.tare_position();
  left_mtr2.tare_position();
  right_mtr.tare_position();
  right_mtr2.tare_position();

  left_mtr.move_absolute(encoderUnits*direction,speed*direction);
  left_mtr2.move_absolute(encoderUnits*direction,speed*direction);
  right_mtr.move_absolute(encoderUnits*direction,speed*direction);
  right_mtr2.move_absolute(encoderUnits*direction,speed*direction);
  if(direction>0){
    while(left_mtr.get_position()<encoderUnits||right_mtr.get_position()<encoderUnits){
      if(left_mtr.get_position()>encoderUnits){
        left_mtr2.move_velocity(0);
      }
      if(right_mtr.get_position()>encoderUnits){
        right_mtr2.move_velocity(0);
      }
      delay(5);
    }
  }else{
    while(left_mtr.get_position()>encoderUnits||right_mtr.get_position()>encoderUnits){
      if(left_mtr.get_position()<encoderUnits){
        left_mtr2.move_velocity(0);
      }
      if(right_mtr.get_position()<encoderUnits){
        right_mtr2.move_velocity(0);
      }
      delay(5);
    }
  }
  delay(550);
}

/*-------------------------------------------------------------------------------------------------------------
| --Turn Method--
|   - Rotates the robot a certain amount of degrees [if Degrees is negative it will rotate counterClockwise]
-------------------------------------------------------------------------------------------------------------*/
void turn(int degrees,int speed){

  pros::Motor left_mtr(leftPort);
	pros::Motor left_mtr2(leftPort2,true);
	pros::Motor right_mtr(rightPort,true);
	pros::Motor right_mtr2(rightPort2);

	double wheelApart = 14.5;//Inches between the 2 traction wheels
  double rotationPointBack = 1.5; //how far back is the center of rotation
  double ma = 1.5;

  int direction = 2*(degrees>0)-1; // Gets the directionallity of degrees: clockwise being positive
  if(degrees < 0){degrees = degrees*-1;} //Gets the absolute of degrees
  double rad = sqrt( pow(wheelApart/2,2) + pow(rotationPointBack,2) ); // Hopefully getting the radius out of the "circle"
  double arc = rad*(degrees*(pi/180)); //gets the Arc length that the wheel will have to travel
  double rotations = arc/(wheelDiameter*pi); //gets the amount of revolutions the wheel will have to do in order to move the arc length
  double encoderUnits = rotations*900*ma; //Gets the amount of encoder units that the motor will have to get to in order to complete the amount of revolutions

  left_mtr.move_velocity(0);
  left_mtr2.move_velocity(0);
  right_mtr.move_velocity(0);
  right_mtr2.move_velocity(0);

  left_mtr.tare_position();
  left_mtr2.tare_position();
  right_mtr.tare_position();
  right_mtr2.tare_position();

  left_mtr.move_absolute(encoderUnits*direction,speed*direction);
  left_mtr2.move_absolute(encoderUnits*direction,speed*direction);
  right_mtr.move_absolute(-encoderUnits*direction,-speed*direction);
  right_mtr2.move_absolute(-encoderUnits*direction,-speed*direction);

  if(direction>0){
    while( (left_mtr.get_position()<=encoderUnits)||(right_mtr.get_position()>=-encoderUnits) ){
      if(left_mtr.get_position()>=encoderUnits){
        left_mtr2.move_velocity(0);
      }
      if(right_mtr.get_position()<=-encoderUnits){
        right_mtr2.move_velocity(0);
      }
      delay(5);
    }
  }
  if(direction<0){
    while( (left_mtr.get_position()>=-encoderUnits)||(right_mtr.get_position()<=encoderUnits) ){
      if(left_mtr.get_position()<=-encoderUnits){
        left_mtr2.move_velocity(0);
      }
      if(right_mtr.get_position()>=encoderUnits){
        right_mtr2.move_velocity(0);
      }
      delay(5);
    }
  }
  delay(500);

}

/*------------------------------------------------------------------
| --intakeActive Method--
|   - It will set the intake to intake (1), reverse (-1), or stop (0)
------------------------------------------------------------------*/
void intakeActive(int direction){
	pros::Motor intake(intakePort, true);
  intake.move_velocity(200*direction);
}


/*
From the motor product page:
1800 ticks/rev with 36:1 gears
900 ticks/rev with 18:1 gears
300 ticks/rev with 6:1 gears
*/
