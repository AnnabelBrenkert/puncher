#include "main.h"
#include "autons.hpp"
#include "pros/misc.h"
#include "pros/motors.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

/*Variable Definitions*/

    /*hang Variables*/
bool lastKnownButtonAState; 
int hangState = 0;

    /*puncher variables*/
bool lastKnownButtonUpState; 
int puncherState = 0;

    /*Vwing Variables*/
bool lastKnownButtonR2State; 
int VwingState = 0;

/*End of Variable Definitions*/

// Chassis constructor
ez::Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  {-12, -4, -10}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{16, 3, 13}

  // IMU Port
  ,14

  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
  ,3.25

  // Cartridge RPM
  ,600

  // External Gear Ratio (MUST BE DECIMAL) This is WHEEL GEAR / MOTOR GEAR
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 84/36 which is 2.333
  // eg. if your drive is 60:36 where the 36t is powered, your RATIO would be 60/36 which is 0.6
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 36/60 which is 0.6
  ,0.6
);

const int DRIVE_SPEED = 600; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 300;
const int SWING_SPEED = 300;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0); // Sets the active brake kP. We recommend 0.1.
  chassis.opcontrol_curve_default_set(7.25, 7.25); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU 
  /*
  ez::as::auton_selector.autons_add({
    Auton("Example Drive\n\nDrive forward and come back.", drive_example),
    Auton("Example Turn\n\nTurn 3 times.", turn_example),
    Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
    Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
    Auton("Swing Example\n\nSwing in an 'S' curve", swing_example),
    Auton("Combine all 3 movements", combining_movements),
    Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  });
*/
  // Initialize chassis and auton selector
  chassis.initialize();
  Vwings.set_value(0);
  Hwings.set_value(0);
puncher.set_brake_mode(MOTOR_BRAKE_COAST);
intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
 // ez::as::initialize();
  master.rumble(".");
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



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
  chassis.pid_targets_reset(); // Resets PID targets to 0
  chassis.drive_imu_reset(); // Reset gyro position to 0
  chassis.drive_sensor_reset(); // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency

 // ez::as::auton_selector.selected_auton_call(); // Calls selected auton from autonomous selector

puncher.move_voltage(127);
  pros::c::delay(27000);
puncher.move_voltage(0);
  pros::delay(50);

chassis.pid_turn_set(-15, TURN_SPEED);
  chassis.pid_wait();
chassis.pid_drive_set(200, DRIVE_SPEED, true);
  chassis.pid_wait(); 
chassis.pid_turn_set(15, TURN_SPEED);
  chassis.pid_wait();
Hwings.set_value(true);
chassis.pid_drive_set(200, DRIVE_SPEED, true);
  chassis.pid_wait(); 
chassis.pid_drive_set(-72, DRIVE_SPEED, true);
  chassis.pid_wait(); 
chassis.pid_turn_set(90, TURN_SPEED);
  chassis.pid_wait();
chassis.pid_drive_set(72, DRIVE_SPEED, true);
  chassis.pid_wait(); 
chassis.pid_turn_set(15, TURN_SPEED);
  chassis.pid_wait();
chassis.pid_drive_set(72, DRIVE_SPEED, true);
  chassis.pid_wait(); 

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
  // This is preference to what you like to drive on
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);
  
  while (true) {
    

    chassis.opcontrol_tank(); 

  //puncher code
  if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) != lastKnownButtonUpState)
		{
			lastKnownButtonUpState = master.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && puncherState == 0 || puncherState == 2)
			{
				puncherState = 1;
			}
			else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP) && puncherState == 1)
			{
				puncherState = 0;
      }
    }

    switch (puncherState)
		{
			case 0:
				puncher.move(0);
				break;
			case 1:
				puncher.move(127);
				break;
    }

  /* Intake/outtake Code*/
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1))
		{
			intake.move(127);
		}
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2))
		{
			intake.move(-127);
		}
		else 
		{
			intake.move(0);
		}

    /*Vertical Wing Code*/
   	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) != lastKnownButtonR2State)
		{
			lastKnownButtonR2State = master.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && VwingState == 0 || VwingState == 2)
			{
				VwingState = 1;
			} 
			else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2) && VwingState == 1)
			{
				VwingState = 0;
			}
		}  

    switch (VwingState)
    {
      case 0:
			 Vwings.set_value(0);
      pros::delay(10);
      break;
			
      case 1:
				Vwings.set_value(1);
      pros::delay(10);
				break;
    }

    /*Horizontal Wing Code*/
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
		{
			Hwings.set_value(1);
      pros::delay(10);
		}
		else 
		{
			Hwings.set_value(0);
			pros::delay(10);
		}

    //hanging code
   	if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A) != lastKnownButtonAState)
		{
			lastKnownButtonAState = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);
			if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && hangState == 0 || hangState == 2)
			{
				hangState = 1;
			} 
			else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A) && hangState == 1)
			{
				hangState = 0;
			}
		}  

    switch (hangState)
    {
      case 0:
			 hang.set_value(0);
      pros::delay(10);
      break;
			
      case 1:
				hang.set_value(1);
      pros::delay(10);
				break;
    }

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
