#include "main.h"
//Helpy Functions
void setDrive(int left, int right){

  RightBack = right;
  RightMid = right;
  RightFront = right;
  LeftBack = left;
  LeftMid = left;
  LeftFront = left;
}


//Driver Control Functions
void SetDriveMotors() {
int ForwardStick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
int TurnStick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

setDrive(ForwardStick+TurnStick, ForwardStick-TurnStick);


//Battery Save
if (abs(ForwardStick) < 5){ForwardStick = 0;}
if (abs(TurnStick) < 5){TurnStick = 0;}
}
