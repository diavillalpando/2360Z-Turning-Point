extern int mainAuton;

//Ports for the Brain
extern int leftPort;
extern int leftPort2;
extern int rightPort;
extern int rightPort2;
extern int puncherPort;
extern int intakePort;
extern int anglePort;
extern int armPort;

//Sensors
extern int visionPort;
extern int indexSensor;

//Vision Sensor
extern double findFlag(int phase, bool print);
extern double findFlag2();
extern int vision_blue;
extern int vision_red;
extern int vision_green;
extern int enemy_color;
extern int timer1;

//various shots
extern int shotA;
extern int shotB;
extern int shotX;
extern int shotA2;
extern int shotB2;
extern int shotX2;

//Things that should never change
extern const double wheelDiameter;
extern const double pi;

//User Interface Stuff
extern void UIFunc();
extern void contConsole(const char *txt);
extern const char * autonDescription(int i);
extern bool redTeam;
