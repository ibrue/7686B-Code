#include "main.h"
//Helpy Functions

void TimeWarn() {
  
  pros::delay((1_min + 34_s).convert(1_ms));
 	pros::c::controller_rumble(pros::E_CONTROLLER_MASTER, ". --");
}