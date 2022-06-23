#include "main.h"

//Helpy functions
void setFlywheel(int speed){
  Flywheel = speed;
  }

void setIntake(int index){
  Intake = index;
  }


//Driver Control functions
void SetFlywheelMotors(){
  int flywheelpower;
  int intakepower;

if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
flywheelpower = 105;
intakepower = 127;
}

else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
flywheelpower = 127;
intakepower = -127;
}

else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A)){
flywheelpower = 127;
intakepower = -50;
}

else {
intakepower = 0;
flywheelpower = 105;

}

setFlywheel(flywheelpower);
setIntake(intakepower);


}
