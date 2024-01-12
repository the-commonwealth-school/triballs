#include "main.h"

/* Replace later when we figure out what ports map to what. */
#define LWHEEL_PORT 1   /* Left wheel. */
#define RWHEEL_PORT 2   /* Right wheel. */
#define LARM_PORT 3     /* Left arm thing. */
#define RARM_PORT 4     /* Right arm thing. */

/* 
   Right-side motors are reversed.
   Will need to confirm whether this or the opposite is necessary later on.
*/
pros::Motor lwheel(L_WHEEL_PORT, false);
pros::Motor rwheel(R_WHEEL_PORT, true);
pros::Motor larm(L_ARM_PORT, false);
pros::Motor rarm(R_ARM_PORT, true);
pros::Controller controller(CONTROLLER_MASTER);

/*
   A simple test callback function for brain's center button.
*/
void on_center_btn() {
   static bool pressed = false;
   pressed = !pressed;
   pressed ? pros::lcd::set_text(2, "( ͡° ͜ʖ ͡°)") : pros::lcd::clear_line(2);
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

 void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");
   pros::lcd::register_btn1_cb(on_center_btn);
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
void autonomous() {}

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
  while (true) {
    int left_y = controller.get_analog(ANALOG_LEFT_Y);
    int right_y = controller.get_analog(ANALOG_RIGHT_Y);

    left_motor.move(left_y);
    right_motor.move(right_y);

    pros::delay(2);
  }
}
