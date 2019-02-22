//--Simple methods--//
extern void drive(int inches,int speed); //Moves the robot a certain amount of inches[if Inches is negative it will drive backwards]
extern void turn(int degrees,int speed); //Rotates the robot a certain amount of degrees [if Degrees is negative it will rotate counterClockwise]
extern void lift(int level, bool wait); //sets the lift to a certain "Level"[Level: 0 = floor, 1 = low post, 2 = High post, 3 = max height]
extern void lift(bool upDown);
extern void flip(int degree, int speed);
extern void flip(int degree); //sets the claw to any given degree from its tare
extern void flip();
extern void autonomous();

//--Complex Methods--//
extern void shoot(int rpm);
extern void intakeActive(bool active);
extern void indexUntil();
