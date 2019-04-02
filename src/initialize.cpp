#include "main.h"
#include "MyHeaders/globalVariables.h"
#include "MyHeaders/autonMethods.h"
//#include "customUI.cpp"jhg

int mainAuton;
int leftPort;
int leftPort2;
int rightPort;
int rightPort2;
int puncherPort;
int intakePort;
int anglePort;
int armPort;
int visionPort;
int indexSensor;
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
	leftPort = 10;
	leftPort2 = 9;
	rightPort = 20;
	rightPort2 = 12;
	puncherPort = 1;
	intakePort = 3;
	anglePort = 11;
	armPort = 2;

	visionPort = 16;
	indexSensor = 1;
	//--definitions of the ticks for the various shots--//
	shotA = 345;
	shotB = 200;
	shotX = 191;

	shotA2 = 900;
	shotB2 = 881;
	shotX2 = 703;

	//--Defines what vision sensor signatures correspond to what color--//
	vision_green = 1;
	vision_red = 2;
	vision_blue = 3;

	enemy_color = vision_red; //By Default the robot is part of the Blue alliance

	redTeam = true;
}

void disabled() {

} //in Between Autonomous & opControl

void competition_initialize() { //After Initialize but Before Autonumous


}
