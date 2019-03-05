#include "main.h"
#include "MyHeaders/globalVariables.h"
#include "MyHeaders/autonMethods.h"
#include "inputMethods.cpp"
using namespace pros::literals;

void opcontrol() {

	//--Motor Definitions--//
	pros::Motor left_mtr(leftPort);
	pros::Motor left_mtr2(leftPort2,true);
	pros::Motor right_mtr(rightPort,true);
	pros::Motor right_mtr2(rightPort2);
	pros::Motor puncher(puncherPort);
	pros::Motor intake(intakePort);
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

		//--Arm--//
		arm.move_velocity((cont.l1-cont.l2)*200);

		//--Puncher--//
		puncher.move_velocity(200*cont.r2);

    //--Intake--//
		int reverseButt = -2*(cont.right)+1;
		intake.move_velocity(200*partner.btnY*reverseButt);

		//--Vision Sensor Testing--//
    //double whereAreThou = findFlag();

		pros::delay(10);

	}

}

/*
HOW TO CONSOLE
std::string text = "FlyWheel: "+ std::to_string(flywheel.get_actual_velocity()) + " RPM";
contConsole(text.c_str()); indexButton = pros::c::adi_digital_read(indexSensor);
*/
