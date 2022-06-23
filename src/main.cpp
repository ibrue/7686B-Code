#include "main.h"
#include "gif-pros/gifclass.hpp"


/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {


}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

	LeftFront.set_brake_mode(MOTOR_BRAKE_BRAKE);
	LeftMid.set_brake_mode(MOTOR_BRAKE_BRAKE);
	LeftBack.set_brake_mode(MOTOR_BRAKE_BRAKE);
	RightFront.set_brake_mode(MOTOR_BRAKE_BRAKE);
	RightMid.set_brake_mode(MOTOR_BRAKE_BRAKE);
	RightBack.set_brake_mode(MOTOR_BRAKE_BRAKE);

	ProfileConstraint moveLimit({5.3_ftps, 6_ftps2, 5_ftps2, 27_ftps3});
	  std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
	    .withMotors({14, 15, 16}, {17, 18, 20})
			.withSensors(
			ADIEncoder{'C', 'D'}, // left encoder in ADI ports A & B
			ADIEncoder{'A', 'B', true},  // right encoder in ADI ports C & D (reversed)
			ADIEncoder{'E', 'F'}  // middle encoder in ADI ports E & F
			)
	    .withDimensions({AbstractMotor::gearset::blue, 4.0/3.0}, {{2.75_in, 1.25_ft},   imev5BlueTPR})
	    .build();

			//TUNING
			FFVelocityController leftController(0.23, .025, .01, 1.6, .1);
      FFVelocityController rightController(0.23, .025, .01, 1.6, .1);

	  std::shared_ptr<AsyncMotionProfiler> profiler = AsyncMotionProfilerBuilder()
	    .withOutput(chassis)
			.withLinearController(leftController, rightController)
	    .withProfiler(std::make_unique<SCurveMotionProfile>(moveLimit))
	    .build();

	  profiler->setTarget(2_ft, true);
		profiler->setTarget(-2_ft, true);




	}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
		// TimeWarn();
		LeftFront.set_brake_mode(MOTOR_BRAKE_COAST);
		LeftMid.set_brake_mode(MOTOR_BRAKE_COAST);
		LeftBack.set_brake_mode(MOTOR_BRAKE_COAST);
		RightFront.set_brake_mode(MOTOR_BRAKE_COAST);
		RightMid.set_brake_mode(MOTOR_BRAKE_COAST);
		RightBack.set_brake_mode(MOTOR_BRAKE_COAST);
	Gif gif("/usd/mygif.gif", lv_scr_act());
	 	 pros::c::controller_rumble(pros::E_CONTROLLER_MASTER, "-.");
	while (true) {
	//Control the drive
		SetDriveMotors();
	//Control Flywheel?
		SetFlywheelMotors();


		pros::delay(20);
	}
}
