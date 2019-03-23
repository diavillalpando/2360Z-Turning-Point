#include "main.h"
#include "MyHeaders/globalVariables.h"

double findFlag(){ //Gets the coordinates of the nearest enemy
	pros::Vision vision_sensor (visionPort);
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(leftPort);
	pros::Motor left_mtr2(leftPort2);
	pros::Motor right_mtr(rightPort,true);
	pros::Motor right_mtr2(rightPort2,true);

	int vision_xmiddle = 158;
	int vision_ymiddle = 106;
	int smallestDistance = 316;
	int nearestDist = -1;
	int closestFlag = -1;
	int turnDir = 0;
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
				if ( sqrt((xdist^2) + (ydist^2))  <  (0.5*green_arr[i][2]) )
				{
					flag_arr[flagCount][0] = green_arr[i][0];
					flag_arr[flagCount][1] = green_arr[i][1];
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
			if (abs(vision_xmiddle - flag_arr[flagCount][0]) < abs(smallestDistance))
			{
				smallestDistance = (vision_xmiddle - flag_arr[flagCount][0]);
				closestFlag = i;
			}
		}
		nearestDist = (vision_xmiddle - flag_arr[closestFlag][0]);
		if (nearestDist > 0)
		{turnDir = 1;}
		else
		{turnDir = -1;}
	}
	else
	{
		nearestDist = -1;
	}


	//std::cout << "Objects Detected: " << obj_count << std::endl;
	//for (int i = 0; i < 10; i++)
	//{std::cout << flag_arr[i][0] << ", " << flag_arr[i][1] << std::endl;}
	std::cout << "Nearest X: " << flag_arr[closestFlag][0] << std::endl;
	std::cout << "Nearest Dist: " << nearestDist  << std::endl;



	if ((master.get_digital(DIGITAL_A)) && (abs(nearestDist) > 6))
	{
		right_mtr.move(turnDir * 40 );
		right_mtr2.move(turnDir * 40  );
		left_mtr.move( -turnDir * 40  );
		left_mtr2.move( -turnDir * 40 );
	}
	return(0);
}
