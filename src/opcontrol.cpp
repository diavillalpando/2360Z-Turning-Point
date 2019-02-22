#include "main.h"
#include "MyHeaders/globalVariables.h"
#include "MyHeaders/autonMethods.h"
#include "inputMethods.cpp"
using namespace pros::literals;

void opcontrol() {

	//--Motor Definitions--//
	pros::Motor left_mtr(leftPort);
	pros::Motor right_mtr(rightPort,true);
	pros::Motor flywheel(flywheelPort);
	pros::Motor index(indexPort, true);
	pros::Motor intake(intakePort, true);
	pros::Motor liftL(liftLPort, true);
	pros::Motor liftR(liftRPort);
	pros::Motor claw(clawPort, true);

liftR.tare_position();

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
		left_mtr.move( cont.lJoy  );
		right_mtr.move( cont.rJoy );

		//--CLaw--//
		if(cont.r1){flip(45);}
    if(cont.r2){flip(90);}
		if(!cont.r2&&!cont.r1){flip(-1);}

		//--Lift--//
		if(cont.l1){
			liftR.move_velocity(200);
			liftL.move_velocity(200);
		}
		if(cont.l2){
			liftR.move_velocity( -100);
			liftL.move_velocity( -100);
		}
		if(!cont.l2&&!cont.l1){
			liftR.move_velocity(0);
			liftL.move_velocity(0);
		}

		//--Flywheel--//
		flywheel.move_velocity(100*partner.up);

		if(partner.btnA && partner.up ){
			shoot(shotA);
		}
		if(partner.btnB && partner.up ){
			shoot(shotB);
		}
		if(partner.btnX && partner.up ){
			shoot(shotX);
		}

    //--Intake/Indexer--//
		int reverseButt = -2*(partner.down)+1;
		index.move_velocity(80*partner.btnY*reverseButt*(!pros::c::adi_digital_read(indexSensor)));
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
