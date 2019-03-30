extern void autonomous();

//Drive Methods
extern void drive(int inches,int speed); //Moves the robot a certain amount of inches[if Inches is negative it will drive backwards]
extern void turn(int degrees,int speed); //Rotates the robot a certain amount of degrees [if Degrees is negative it will rotate counterClockwise]

//Shooting Methods
extern void aim(int angle, bool wait);
extern void aimTick(int ticks, bool wait);
extern void shoot();
extern void doubleShot();
extern void shoot(int degree);
extern void intakeActive(int direction);

//Arm Methods
extern void armPos(int level, bool wait);
