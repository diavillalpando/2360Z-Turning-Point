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
	pros::Motor arm(armPort);

	//--Initializes instances of Controllers--//
	ControllerCustom cont(1);
	ControllerCustom partner(2);

  while(true){

		//--Updates the values on the controllers--//
		cont.update();
		partner.update();

    //--Auton Testing--//
		if(cont.up&&cont.right&&cont.down&&cont.left){
			autonomous();
		}

		//--Drive--//
		right_mtr.move( cont.rJoy );
		right_mtr2.move( cont.rJoy );

		left_mtr.move( cont.lJoy  );
		left_mtr2.move( cont.lJoy  );

		//--Aimer--//
		aimer.move_velocity((cont.up-cont.down)*200);
		if(cont.btnA==1){aimTick(shotA, false);}
		if(cont.btnB==1){aimTick(shotB, false);}
		if(cont.btnX==1){aimTick(shotX, false);}

		std::string text = "Aimer: "+ std::to_string(aimer.get_position()) + " Ticks";
		contConsole(text.c_str());

		//--Puncher--//
		puncher.move_velocity(200*cont.r2);

    //--Intake--//
		intake.move_velocity(200*(partner.l1-partner.l2));

		//--Arm--//
		arm.move_velocity(200*(cont.l1-cont.l2));
		if(cont.r1){arm.set_brake_mode(E_MOTOR_BRAKE_HOLD);
		}else{arm.set_brake_mode(E_MOTOR_BRAKE_COAST);}

		//--Vision Sensor Testing--//
    //double whereAreThou = findFlag();

		pros::delay(10);

	}

}

/*
HOW TO CONSOLE
std::string text = "FlyWheel: "+ std::to_string(flywheel.get_actual_velocity()) + " RPM";
contConsole(text.c_str());


indexButton = pros::c::adi_digital_read(indexSensor);
*/
