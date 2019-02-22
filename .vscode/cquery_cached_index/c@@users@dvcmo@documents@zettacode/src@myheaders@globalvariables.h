
//Ports for the Brain
extern int mainAuton;
extern int leftPort;
extern int rightPort;
extern int flywheelPort;
extern int indexPort;
extern int intakePort;
extern int liftLPort;
extern int liftRPort;
extern int clawPort;

//Sensors
extern int visionPort;
extern int intakeSensor;
extern int indexSensor;
extern int liftSensor;

//Vision Sensor
extern double findFlag();
extern double findFlag2();
extern int vision_blue;
extern int vision_red;
extern int vision_green;
extern int enemy_color;

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
