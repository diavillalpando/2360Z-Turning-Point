#include "main.h"
#include "MyHeaders/globalVariables.h"

double findFlag(){ //Gets the x distance to the center of the camera of the object whose position is closest to the center;
pros::Vision vision_sensor(visionPort);
int green_objects[10][4]; //10 objects, [0] = x pos; [1] = y pos; [2] = width; [3] = height
int enemy_objects[10][4]; //10 objects, [0] = x pos; [1] = y pos; [2] = width; [3] = height
int flags[10]; //positions where the flags are; the value is -1 if there is no flag stored
double distance = 0.6;
int centerFlag = -1;
int cameraCenter = 100;

std::cout << "------------Flag Pos------------" << std::endl;

//--Stores values into the arrays--//
int currentColor = enemy_color;
for (int i = 0; i < 2; i++){
	for(int j = 0; j < 10; j++){
			vision_object_s_t current = vision_sensor.get_by_sig(j,currentColor);
			if(currentColor==enemy_color){
				enemy_objects[j][0] = current.x_middle_coord;
				enemy_objects[j][1] = current.y_middle_coord;
				enemy_objects[j][2] = current.width;
				enemy_objects[j][3] = current.height;
			}else{
				green_objects[j][0] = current.x_middle_coord;
				green_objects[j][1] = current.y_middle_coord;
				green_objects[j][2] = current.width;
				green_objects[j][3] = current.height;
			}
	}
	currentColor = vision_green;
}
//--Gets locations for the flags--//
for(int i = 0; i<10; i++){
	double radiusX = green_objects[i][2]*distance;
	double radiusY = green_objects[i][3]*distance;
	flags[i] = -1;
	for(int j = 0; j<10; j++){
		bool heightDiff = abs(green_objects[i][1]-enemy_objects[j][1])<=radiusY;
		bool widthDiffR =abs((green_objects[i][0]+green_objects[i][2]/2)-(enemy_objects[j][0]-enemy_objects[j][2]/2)) <= radiusX;
		bool widthDiffL =abs((green_objects[i][0]-green_objects[i][2]/2)-(enemy_objects[j][0]+enemy_objects[j][2]/2)) <= radiusX;
		if(heightDiff&&(widthDiffR||widthDiffL)){
			flags[i] = enemy_objects[j][0];
			j = 10;
		}
	}
}
std::cout << flags[0] << std::endl;
std::cout << flags[1] << std::endl;
std::cout << flags[2] << std::endl;
std::cout << flags[3] << std::endl;
std::cout << flags[4] << std::endl;
std::cout << flags[5] << std::endl;
std::cout << flags[6] << std::endl;
std::cout << flags[7] << std::endl;
std::cout << flags[8] << std::endl;
std::cout << flags[9] << std::endl;
//--Finds the closest flag to the center--//
for(int i = 0; i<10; i++){
	if( abs(flags[i]-cameraCenter) < abs(centerFlag-cameraCenter) ){
		centerFlag = flags[i];
	}
}

std::cout << "-------------Finish-------------" << std::endl;
return centerFlag;
}
//------------------------------------------------------------------------------------------------------------------------------------------------
//ANDY'S CODE [FEB 16]//
double findFlag2(){ //Gets the x distance to the center of the camera of the object whose position is closest to the center;
	pros::Vision vision_sens(visionPort);
	int team_xpos[10];
	int nearest_dist = 158;
	for (int i = 0; i < 10; i++){
		vision_object_s_t ooflol = vision_sens.get_by_sig(i,enemy_color);
		if ((abs(ooflol.x_middle_coord) < 316) && (abs(ooflol.x_middle_coord) > 0))
		{
				team_xpos[i] = ooflol.x_middle_coord;
		}
		else
		{
				team_xpos[i] = -1;
		}
	}
	for(int i = 0; i < 10; i++)
	{
		if ((nearest_dist > abs(team_xpos[i]-158)) && (team_xpos[i] != -1))
		{
				nearest_dist = (abs(team_xpos[i]-158));
		}
	}
	std::cout << nearest_dist << std::endl;
	return 0;
}
