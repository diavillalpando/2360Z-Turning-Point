#include "main.h"
#include "MyHeaders/globalVariables.h"
#include "MyHeaders/autonMethods.h"
//#include "customUI.cpp"jhg

int mainAuton;
extern int leftPort;
extern int leftPort2;
extern int rightPort;
extern int rightPort2;
extern int puncherPort;
extern int intakePort;
extern int anglePort;
extern int armPort;
int visionPort;
int shotA;
int shotA2; //this is just a test to see what happens
int shotB;
int shotB2;
int shotX;
int shotX2;
int vision_blue;
int vision_red;
int vision_green;
int enemy_color;
bool redTeam;

//--Variables that should never change--//
const double wheelDiameter = 4;
const double pi = 3.141593;

void initialize(){  //First Thing to Run
	mainAuton=0;

	//pros::Task userInterface((task_fn_t)UIFunc,NULL,TASK_PRIORITY_DEFAULT+2,TASK_STACK_DEPTH_DEFAULT,"CustomUserInterface");//Starts the custom User Interface
	//pros::Task intakeTask((task_fn_t)smartIntake,NULL,TASK_PRIORITY_DEFAULT+1,TASK_STACK_DEPTH_DEFAULT,"AutonumousIntake");//Starts the custom Intake Method

	pros::Task userInterface((task_fn_t)UIFunc);

	//--Defines the Ports for the Various Subsystems--//
	leftPort = 20;
	leftPort2 = 19;
	rightPort = 18;
	rightPort2 = 17;
	puncherPort = 16;
	intakePort = 15;
	anglePort = 14;
	armPort = 13;

	visionPort = 1;

	//--definitions of the times for the various shots--// [OLD]
	shotA = 145;
	shotB = 180;
	shotX = 200;

	shotA2 = 100;
	shotB2 = 150;
	shotX2 = 200;

	//--Defines what vision sensor signatures correspond to what color--//
	vision_blue = 1;
	vision_red = 2;
	vision_green = 3;
	enemy_color = vision_blue; //By Default the robot is part of the Blue alliance

	redTeam = true;
}

void disabled() {

} //in Between Autonomous & opControl

void competition_initialize() { //After Initialize but Before Autonumous


}
