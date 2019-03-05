#include "main.h"
#include "MyHeaders/globalVariables.h"
#include "MyHeaders/autonMethods.h"

void autonomous() {
  int red = 2*redTeam-1;
  //---------------------//
  if(mainAuton==0){//If No autonomous is selected

  }
  //---------------------//
}
const char * autonDescription(int i){
	std::string description = "No Autonumous"; //-0-//
  if(i==1){   description = "empty";} //-1-//
  if(i==2){   description = "empty";} //-2-//
  if(i==3){   description = "empty";} //-3-//
  if(i==4){   description = "empty";} //-4-//
  if(i==5){   description = "empty";} //-5-//
  if(i==6){   description = "empty";} //-6-//
  if(i==7){   description = "empty";} //-7-//
  if(i==8){   description = "empty";} //-8-//
  if(i==9){   description = "empty";} //-9-//
  if(i==10){  description = "empty";} //-10-//
  if(i==11){  description = "empty";} //-11-//
  if(i==12){  description = "empty";} //-12-//

	return description.c_str();
}

// 05/01/2019
