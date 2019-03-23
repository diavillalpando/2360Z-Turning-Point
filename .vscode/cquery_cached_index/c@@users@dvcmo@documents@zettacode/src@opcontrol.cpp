#include "main.h"
#include "MyHeaders/globalVariables.h"
#include "MyHeaders/autonMethods.h"
#include "inputMethods.cpp"
using namespace pros::literals;

void opcontrol() {

	//--Motor Definitions--//
	pros::Motor left_mtr(leftPort);
	pros::Motor left_mtr2(leftPort2);
	pros::Motor right_mtr(rightPort,true);
	pros::Motor right_mtr2(rightPort2,true);
	pros::Motor puncher(puncherPort);
	pros::Motor intake(intakePort,true);
	pros::Motor aimer(anglePort);
	pros::Motor arm(armPort,true);

	//--Initializes instances of Controllers--//
	ControllerCustom cont(1);
	ControllerCustom partner(2);

	bool lowCapMode = false;
	int armMode = 1; //0 = disable and put away, 1 = carry/prevent puncher from hitting; 2 = lowCaps
	bool r2Pressed = false;
	bool firstShot = true;

	arm.tare_position();
	aimer.tare_position();
	aimer.set_brake_mode(E_MOTOR_BRAKE_HOLD);
	aimTick(shotA, false);

  while(true){

		//--Updates the values on the controllers--//
		cont.update();
		partner.update();

    //--Auton Testing--//
		if(!cont.up&&cont.right&&!cont.down&&cont.left){
			autonomous();
		}

		//--Drive--//
		right_mtr.move( cont.rJoy );
		right_mtr2.move( cont.rJoy );

		left_mtr.move( cont.lJoy  );
		left_mtr2.move( cont.lJoy  );

		//--Aimer--//
		if(partner.btnA==1&&partner.up){aimTick(shotA, false);}//if(cont.btnA==1){aimTick(shotA, false);}
		if(partner.btnB==1&&partner.up){aimTick(shotB, false);}//if(cont.btnB==1){aimTick(shotB, false);}
		if(partner.btnX==1&&partner.up){aimTick(shotX, false);}//if(cont.btnX==1){aimTick(shotX, false);}
		if(partner.btnA==1&&partner.down){aimTick(shotA2, false);}
		if(partner.btnB==1&&partner.down){aimTick(shotB2, false);}
		if(partner.btnX==1&&partner.down){aimTick(shotX2, false);}



    //std::cout << aimer.get_position()<< std::endl;
		//std::string text = "Aimer: "+ std::to_string(aimer.get_position()) + " Ticks";
		//contConsole(text.c_str());

		//--Puncher--//
		puncher.set_brake_mode(MOTOR_BRAKE_COAST); //puncher.move_velocity(200*cont.r2);
		if(!cont.r2&&r2Pressed){
			r2Pressed = false;
			firstShot = false;
		}
		if(cont.r2&&!r2Pressed&&((puncher.get_position()>=900)||firstShot)){
			shoot();
			r2Pressed = true;
		}



    //--Intake--//
		intake.move_velocity(200*(partner.l1-partner.l2));//intake.move_velocity(200*(cont.r1));

		//--Arm--//
		if(armMode == 0){ //Disable
			if(arm.get_position()>((30/360.0)*(64/12.0)*900)){
				arm.move_absolute(10,200);
			}
			if(arm.get_position()<((30/360.0)*(64/12.0)*900)){
				arm.move_velocity(0);
				arm.set_brake_mode(E_MOTOR_BRAKE_COAST);
			}
		}
		if(armMode == 1){ //Post Mode
		  arm.set_brake_mode(E_MOTOR_BRAKE_HOLD);
		  if(cont.l1){
		    arm.move_absolute(((165/360.0)*(64/12.0)*900),50);
		  }
		  if(cont.l2){
		    arm.move_absolute( ((0/360.0)*(64/12.0)*900) ,100);
		  }
		  if(!cont.l1&&!cont.l2){
		    arm.move_absolute(((45/360.0)*(64/12.0)*900),100);
		  }
		}
		if(armMode == 2){ //Low Cap Mode
		  arm.set_brake_mode(E_MOTOR_BRAKE_HOLD);
		  if(cont.l2){
		    arm.move_absolute(((225/360.0)*(64/12.0)*900),200);
		  }
		  if(!cont.l2){
				if(arm.get_position()<((250/360.0)*(64/12.0)*900)){
					arm.move_absolute(((270/360.0)*(64/12.0)*900),200);
				}
				if(arm.get_position()>((250/360.0)*(64/12.0)*900)){
					arm.move_velocity(0);
					arm.set_brake_mode(E_MOTOR_BRAKE_COAST);
				}
		  }
		}
		if(cont.left){armMode = 0;}
		if(cont.down){armMode = 1;}
		if(cont.up){armMode = 2;}

		//--Vision Sensor Testing--//
    double whereAreThou = findFlag();

		pros::delay(10);

	}

}

/*
HOW TO CONSOLE
std::string text = "FlyWheel: "+ std::to_string(flywheel.get_actual_velocity()) + " RPM";
contConsole(text.c_str());

  arm.set_brake_mode(E_MOTOR_BRAKE_HOLD);
		arm.move_velocity(200*(cont.l1-cont.l2));

indexButton = pros::c::adi_digital_read(indexSensor);
*/
