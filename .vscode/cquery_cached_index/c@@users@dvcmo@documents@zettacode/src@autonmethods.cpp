#include "main.h"
#include "MyHeaders/globalVariables.h"

//-----Calibration Variables-----//
bool aimerCalibrated = false;
bool armCalibrated = false;
//-------------------------------//

/*------------------------------------------------------------------------------------------------
| --Drive Method--
|   - Moves the robot a certain amount of inches[if Inches is negative it will drive backwards]
------------------------------------------------------------------------------------------------*/
void drive(int inches, int speed){
  pros::Motor left_mtr(leftPort);
  pros::Motor left_mtr2(leftPort2);
  pros::Motor right_mtr(rightPort,true);
  pros::Motor right_mtr2(rightPort2,true);

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
	pros::Motor left_mtr2(leftPort2);
	pros::Motor right_mtr(rightPort,true);
	pros::Motor right_mtr2(rightPort2,true);

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
| --aim Method--
|   - UNFINISHED
------------------------------------------------------------------*/
void aim(int angle, bool wait){
  double armLength = 10;
  double anchorDistance = 10;
  double gearCircumference = 2;

  double c = asin((anchorDistance*sin(angle))/armLength);
  double b = 180-angle-c;
  double travelDistance = (armLength*sin(b))/sin(angle);

  double encoderUnits = (travelDistance/gearCircumference)*900;
}

/*------------------------------------------------------------------
| --aimTick Method--
|   - moves the motor a certain amount of ticks
------------------------------------------------------------------*/
void aimTick(int ticks, bool wait){
  pros::Motor aimer(anglePort);

  if(!aimerCalibrated){
    aimer.move_velocity(-50);
    delay(600);
    aimer.tare_position();
    aimer.move_velocity(0);
    aimerCalibrated = true;
  }

  int direction = 2*(ticks>aimer.get_position())-1;

  aimer.move_absolute(ticks, 200*direction);
  aimer.set_brake_mode(E_MOTOR_BRAKE_BRAKE);

  if(!wait){return;}

  if(direction>1){
    while(aimer.get_position()<ticks-10){}
  }
  if(direction<1){
    while(aimer.get_position()>ticks+10){}
  }
  delay(600);
}

/*------------------------------------------------------------------
| --shoot Method--
|   - Fires a ball from the puncher
------------------------------------------------------------------*/
void shoot(){
  pros::Motor puncher(puncherPort);

  puncher.move_relative(900,200);
  puncher.set_brake_mode(MOTOR_BRAKE_COAST);
}

/*------------------------------------------------------------------
| --shoot Method--
|   -
------------------------------------------------------------------*/
void shoot(int degree){
  aimTick(degree,true);
  shoot();
}

/*------------------------------------------------------------------
| --intakeActive Method--
|   - It will set the intake to intake (1), reverse (-1), or stop (0)
------------------------------------------------------------------*/
void intakeActive(int direction){
	pros::Motor intake(intakePort, true);
  intake.move_velocity(200*direction);
}

/*------------------------------------------------------------------------------
| --armPos Method--
|   - Sets the arm to a specific level; level 0 = stored, 1 = carry, 2 = place
------------------------------------------------------------------------------*/
void armPos(int level, bool wait){
  pros::Motor arm(armPort);
  int carryPos = (45/360) * 900 * 12;
  int placePos = (180/360) * 900 * 12;
  if(!armCalibrated){
    arm.move_velocity(-50);
    delay(600);
    arm.tare_position();
    arm.move_velocity(0);
    armCalibrated = true;
  }
  int encoderUnits = carryPos*(level==1)+placePos*(level==2);
  int direction = 2*(encoderUnits>arm.get_position())-1;

  arm.move_absolute(encoderUnits, 200*direction);
  arm.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  if(encoderUnits==0){arm.set_brake_mode(E_MOTOR_BRAKE_COAST);}

  if(!wait){return;}

  if(direction>1){
    while(arm.get_position()<encoderUnits){}
  }
  if(direction<1){
    while(arm.get_position()>encoderUnits){}
  }
  delay(600);

}
/*
From the motor product page:
1800 ticks/rev with 36:1 gears
900 ticks/rev with 18:1 gears
300 ticks/rev with 6:1 gears
*/
