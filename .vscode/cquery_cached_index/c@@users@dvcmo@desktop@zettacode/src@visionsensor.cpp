#include "main.h"
#include "MyHeaders/globalVariables.h"

double findFlag(){ //Gets the coordinates of the nearest enemy
	pros::Vision vision_sensor (visionPort);
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(leftPort);
	pros::Motor left_mtr2(leftPort2);
	pros::Motor right_mtr(rightPort,true);
	pros::Motor right_mtr2(rightPort2,true);
	pros::Motor aimer(anglePort);

	int vision_xmiddle = 158;
	int vision_ymiddle = 106;
	int smallestDistance = 0; //316
	int nearestDistX = -1;
	int nearestDistY = -1;
	int closestFlag = -1;
	int turnDir = 0;
	int tiltDir = 0;
	int obj_count = vision_sensor.get_object_count();
	//Green Array
	int green_arr[10][3]; // 0:x-middle-coord  1:y-middle-coord  2:width  3:height
	for (int i = 0; i < 10; i++) //Declare object lists and set all values within to -1
	{
			for (int j = 0; j < 3; j++)
			{green_arr[i][j] = -1;}
	}
	//Enemy Array
	int enemy_arr[10][2]; // 0:x-middle-coord  1:y-middle-coord
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 2; j++)
		{enemy_arr[i][j] = -1;}
	}
	//Flag Array
	int flag_arr[10][2];
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 2; j++)
		{flag_arr[i][j] = -1;}
	}
	int greenCount = 0; // # of Green objects
	int enemyCount = 0; // # of Enemy objects
	int flagCount = 0;
	int xdist = -1;
	int ydist = -1;

  	vision_object_s_t object_arr[obj_count];
    vision_sensor.read_by_sig(0, vision_green, obj_count, object_arr);
		for (int i = 0; i < obj_count; i++)
		{
			if ((object_arr[i].signature == vision_green) && (greenCount < 10))
			{
				if (object_arr[i].width > 1)
				{green_arr[greenCount][0] = object_arr[i].left_coord + (object_arr[i].width/2);}
				else
				{green_arr[greenCount][0] = object_arr[i].left_coord;}

				if (object_arr[i].height > 1)
				{green_arr[greenCount][1] = object_arr[i].top_coord + (object_arr[i].height/2);}
				else
				{green_arr[greenCount][1] = object_arr[i].top_coord;}

				green_arr[greenCount][2] = ((object_arr[i].width) * (object_arr[i].height));
				greenCount++;
			}
			else if ((object_arr[i].signature == enemy_color) && (enemyCount < 10))
			{
				if (object_arr[i].width > 1)
				{enemy_arr[enemyCount][0] = object_arr[i].left_coord + (object_arr[i].width/2);}
				else
				{enemy_arr[enemyCount][0] = object_arr[i].left_coord;}

				if (object_arr[i].height > 1)
				{enemy_arr[enemyCount][1] = object_arr[i].top_coord + (object_arr[i].height/2);}
				else
				{enemy_arr[enemyCount][1] = object_arr[i].top_coord;}
				enemyCount++;
			}
		}


	if (greenCount > 0)
	{
		for(int i = 0; i < greenCount; i++)
		{
			for (int j = 0; j < enemyCount; j++)
			{
				xdist = abs(green_arr[i][0]-enemy_arr[j][0]);
				ydist = abs(green_arr[i][1]-enemy_arr[j][1]);
				if ( sqrt((xdist^2) + (ydist^2))  <  (0.05*green_arr[i][2]) )
				{
					flag_arr[flagCount][0] = (green_arr[i][0] + enemy_arr[j][0]) / 2;
					flag_arr[flagCount][1] = (green_arr[i][1] + enemy_arr[j][1]) / 2;
					flagCount++;
					break;
				}
			}
		}
	}
	if (flagCount > 0)
	{

		for(int i = 0; i < flagCount; i++)
		{
			if ((flag_arr[i][1]) > abs(smallestDistance))
			{
				smallestDistance = (flag_arr[i][1]);
				closestFlag = i;
			}
		}

		nearestDistX = (vision_xmiddle - flag_arr[closestFlag][0]);
		nearestDistY = (vision_ymiddle - flag_arr[closestFlag][1]);
		if (nearestDistX > 0)
		{turnDir = 1;}
		else
		{turnDir = -1;}
		if (nearestDistY > 0)
		{tiltDir = 1;}
		else
		{tiltDir = -1;}
	}
	else
	{
		nearestDistX = -1;
		nearestDistY= -1;
	}


	std::cout << "Nearest X: " << flag_arr[closestFlag][0] << std::endl;
	std::cout << "Nearest Dist X: " << nearestDistX  << std::endl;
	std::cout << "Nearest Dist Y: " << nearestDistY  << std::endl;


	if (abs(nearestDistX) > 5)
	{
		right_mtr.move_velocity(abs(nearestDistX)* 0.4 * turnDir);
		right_mtr2.move_velocity(abs(nearestDistX) * 0.4 * turnDir);
		left_mtr.move_velocity(-abs(nearestDistX) * 0.4 * turnDir);
		left_mtr2.move_velocity(-abs(nearestDistX)* 0.4 * turnDir);
	}
	else
	{
		right_mtr.move_velocity(0);
		right_mtr2.move_velocity(0);
		left_mtr.move_velocity(0);
		left_mtr2.move_velocity(0);



		if (abs(nearestDistY) > 13)
		{
				if (aimer.get_position() > 700)
				{aimer.move_velocity(-30);}
				else
				 {aimer.move_velocity(-30 * tiltDir);}
		}
		else
		{
			aimer.move_velocity(0);
		}



	}
	return(0);
}
