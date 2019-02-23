#include "main.h"
#include "MyHeaders/globalVariables.h"

bool liftCalibrated = false;
bool clawCalibrated = false;
/*------------------------------------------------------------------------------------------------
| --Drive Method--
|   - Moves the robot a certain amount of inches[if Inches is negative it will drive backwards]
------------------------------------------------------------------------------------------------*/
void drive(int inches, int speed){ //
  pros::Motor left_mtr(leftPort);
	pros::Motor right_mtr(rightPort, true);//bananan

  left_mtr.move_velocity(0);
  right_mtr.move_velocity(0);

  int direction = 2*(inches>0)-1;
  double rotations = inches/(wheelDiameter*pi);
  double ma = 1.5;
  double encoderUnits = rotations*900*ma;

  left_mtr.tare_position();
  right_mtr.tare_position();

  left_mtr.move_absolute(encoderUnits,speed*direction);
  right_mtr.move_absolute(encoderUnits,speed*direction);
  if(direction>0){
    while(left_mtr.get_position()<encoderUnits||right_mtr.get_position()<encoderUnits){
      delay(10);
    }
  }else{
    while(left_mtr.get_position()>encoderUnits||right_mtr.get_position()>encoderUnits){
      delay(10);
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
	pros::Motor right_mtr(rightPort, true);
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
  right_mtr.move_velocity(0);

  left_mtr.tare_position();
  right_mtr.tare_position();

  left_mtr.move_absolute(encoderUnits*direction,speed*direction);
  right_mtr.move_absolute(-encoderUnits*direction,-speed*direction);

  if(direction>0){
    while( (left_mtr.get_position()<=encoderUnits)||(right_mtr.get_position()>=-encoderUnits) ){
      delay(5);
    }
  }
  if(direction<0){
    while( (left_mtr.get_position()>=-encoderUnits)||(right_mtr.get_position()<=encoderUnits) ){
      delay(5);
    }
  }
  delay(500);

}

/*--------------------------------------------------------------------------------------------------------
| --Lift Method--
|   - sets the lift to a certain "Level"[Level: 0 = floor, 1 = low post, 2 = High post, 3 = max height]
--------------------------------------------------------------------------------------------------------*/
void lift(int level, bool wait){

  pros::Motor liftL(liftLPort, true);
	pros::Motor liftR(liftRPort);

	int liftSpeed = 200;
	double lowPost = 1700;
	double highPost = 2120;
	double max = 2400;
  int levelTolerance = 10;

  if(!liftCalibrated){ //zeros the lift if it is the first time the method has been called
    liftL.move_velocity(-50);
    liftR.move_velocity(-50);
    delay(500);
    liftR.move_velocity(0);
    liftL.move_velocity(0);
    liftR.tare_position();
    liftL.tare_position();
    liftCalibrated = true;
  }

  double encoderUnits = (lowPost*(level==1)) + (highPost*(level==2)) + (max*(level==3));
	int direction = 2*(encoderUnits > liftR.get_position())-1;

  if(direction==-1){
    liftSpeed = liftSpeed/2;
  }
  liftR.move_absolute(encoderUnits, liftSpeed*direction);
  liftL.move_absolute(encoderUnits, liftSpeed*direction);

  if(!wait){
    return;
  }

    if(direction>0){
      while( (liftL.get_position()<=encoderUnits)||(liftR.get_position()<=encoderUnits) ){
        delay(5);
      }
    }
    if(direction<0){
      while( (liftL.get_position()>=encoderUnits)||(liftR.get_position()>=encoderUnits) ){
        delay(5);
      }
    }
    delay(500);

}
void lift(bool upDown){
  if(upDown){
    lift(-2,false);
  }
  if(!upDown){
    lift(-1,false);
  }

}
/*-----------------------------------------------------------------
| --Claw Method--
|   - Sets a claw to a given angle in relation to its up position
-----------------------------------------------------------------*/
void flip(int degree,int speed){
  pros::Motor claw(clawPort,true);
  if(!clawCalibrated){
    claw.move_velocity(150);
    delay(200);
    claw.tare_position();
    claw.move_velocity(0);
    clawCalibrated = true;
  }
  if(degree==-1){
    claw.move_velocity(0);
    return ;
  }
  int ma = 3;
  double calculated = (degree/360.0)*-900*ma;
  int direction = 2*(calculated>claw.get_position())-1;

  claw.move_absolute(calculated, speed*direction);
}
void flip(int degree){ //sets the claw to any given angle
  flip(degree,150);
}
void flip(){
  flip(45);
  delay(600);
  flip(100);
}
/*-----------------------------------------------------------------------------------------------
| --Shoot Method--
|   - Automated shot for the flywheel [launch the ball once the flywheel reaches the given speed]
------------------------------------------------------------------------------------------------*/
void shootEncoder(int rpm){
  pros::Motor flywheel(flywheelPort);
	pros::Motor index(indexPort, true);
  pros::ADIEncoder encoder(2, 3); //input:B, output:C
  int speed = 0;
encoder.get_value();
}

void shoot(int rpm){
  pros::Motor flywheel(flywheelPort);
	pros::Motor index(indexPort, true);
  flywheel.move(0);
  int currentSpeed = flywheel.get_actual_velocity();
  delay(5);

  while(currentSpeed>50){
    delay(5);
    currentSpeed = flywheel.get_actual_velocity();
  }
  flywheel.move(127);
  delay(5);
  while(currentSpeed<rpm){
    delay(5);
    currentSpeed = flywheel.get_actual_velocity();
  }
  index.move_relative(350, 200);
  delay(600);
  flywheel.move(0);
  index.move(0);

}

/*---------------------------------------------------------
| --intakeActive Method--
|   - It will set the intake on when True, off when False
---------------------------------------------------------*/
void intakeActive(bool active){
	pros::Motor intake(intakePort, true);
  intake.move_velocity(200*active);
}

/*-----------------------------------------------------------------------------------
| --indexUntil Method--
|   - When called it will activate the intake and index until the button is pressed
-----------------------------------------------------------------------------------*/
void indexUntil(){
  pros::Motor index(indexPort, true);
  pros::Motor intake(intakePort, true);
  int indexButton = 0;
  while(indexButton!=1){
    indexButton = pros::c::adi_digital_read(indexSensor);
    index.move_velocity(100*!indexButton);
    intake.move_velocity(200*!indexButton);
    delay(5);
  }
  index.move_velocity(0);
  intake.move_velocity(0);
}

/*
From the motor product page:
1800 ticks/rev with 36:1 gears
900 ticks/rev with 18:1 gears
300 ticks/rev with 6:1 gears
*/
