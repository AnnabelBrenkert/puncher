#include "autons.hpp"
#include "main.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

const int DRIVE_SPEED = 550; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 300;
const int SWING_SPEED = 300;

///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(10, 0, 100);
  chassis.pid_turn_constants_set(3, 0, 20);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  chassis.slew_drive_constants_set(7_in, 80);
}


  pros::Motor puncher (1, pros::E_MOTOR_GEARSET_06);
  pros::Motor intake (15, pros::E_MOTOR_GEARSET_36);

  #define VWING_PORT 'B'
  pros::ADIDigitalOut Vwings(VWING_PORT);
  #define HWING_PORT 'A'
  pros::ADIDigitalOut Hwings(HWING_PORT);

  #define HANG_PORT 'C'
  pros::ADIDigitalOut hang(HANG_PORT);

  pros::Controller master (pros::E_CONTROLLER_MASTER);

///
// Drive Example
///
void Elems_sixBall() {

//push blue tri to corner
Hwings.set_value(true); 
 pros::delay(50);
Hwings.set_value(false); 

//go and intake mid tri 
 chassis.pid_drive_set(170, DRIVE_SPEED, true);
intake.move_velocity(500);
  pros::delay(1500);
intake.move_velocity(0);

//push tris in  
 chassis.pid_turn_set(130, TURN_SPEED);
  chassis.pid_wait();
Hwings.set_value(true);
intake.move_velocity(-500);
  pros::delay(250);
intake.move_velocity(0);
chassis.pid_drive_set(80, DRIVE_SPEED, true);
  chassis.pid_wait(); 

chassis.pid_drive_set(-30, DRIVE_SPEED, true);
 chassis.pid_wait();

//go and get last mid tri 
 chassis.pid_turn_set(275, TURN_SPEED);
 chassis.pid_wait(); 
 
 chassis.pid_drive_set(60, DRIVE_SPEED, true);
intake.move_velocity(500);
  pros::delay(700);
intake.move_velocity(00);

//drop it off 
chassis.pid_turn_set(150, TURN_SPEED);
chassis.pid_wait(); 
 chassis.pid_drive_set(50, DRIVE_SPEED, true);
intake.move_velocity(-500);
  pros::delay(500);
intake.move_velocity(0);
chassis.pid_wait();

//go and get hang tri 
chassis.pid_turn_set(190, TURN_SPEED);
  chassis.pid_wait();
 chassis.pid_drive_set(90, DRIVE_SPEED, true);
  chassis.pid_wait(); 

/*
chassis.pid_turn_set(300, TURN_SPEED);
  chassis.pid_wait();
chassis.pid_drive_set(72, DRIVE_SPEED, true);
  chassis.pid_wait(); 
intake.move_velocity(500);
  pros::delay(500);
intake.move_velocity(0);
*/

//get matchload 
 //chassis.pid_drive_set(-100, DRIVE_SPEED, true);
chassis.pid_turn_set(275, TURN_SPEED);
Hwings.set_value(true);
chassis.pid_wait();

//push all in 
 chassis.pid_drive_set(-80, DRIVE_SPEED, true);
  chassis.pid_wait();  
chassis.pid_turn_set(200, TURN_SPEED);
  chassis.pid_wait();
Hwings.set_value(false);
chassis.pid_drive_set(-50, DRIVE_SPEED, true);


}

///
// Turn Example
///
void quals_WinPoint() {
//score matchload 
chassis.pid_drive_set(-14, DRIVE_SPEED, true);
 chassis.pid_wait();
chassis.pid_turn_set(-45, TURN_SPEED);
 chassis.pid_wait();
chassis.pid_drive_set(-85, DRIVE_SPEED, true);
 chassis.pid_wait();
chassis.pid_turn_set(0, TURN_SPEED);
 chassis.pid_wait();
chassis.pid_drive_set(15, DRIVE_SPEED, false);
 chassis.pid_wait();
chassis.pid_drive_set(-25, DRIVE_SPEED, false);
 chassis.pid_wait();
chassis.pid_drive_set(15, DRIVE_SPEED, true);
 chassis.pid_wait();
chassis.pid_turn_set(165, TURN_SPEED);
 chassis.pid_wait();
chassis.pid_drive_set(-35, DRIVE_SPEED, true);
chassis.pid_wait();
Vwings.set_value(true);
chassis.pid_drive_set(-30, DRIVE_SPEED, true);
 chassis.pid_wait();
chassis.pid_turn_set(95, TURN_SPEED);
 chassis.pid_wait();
chassis.pid_drive_set(-15, DRIVE_SPEED, true);
 chassis.pid_wait();
 Vwings.set_value(false);
chassis.pid_turn_set(90, TURN_SPEED);
 chassis.pid_wait();
chassis.pid_drive_set(-100, DRIVE_SPEED, true);
 chassis.pid_wait();


}

///
// Combining Turn + Drive
///
void skills() {
 //drive to goal and score matchload //////////////////////////////////////////////////////////////////////////////////////////////
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

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  //drive to goal and score matchload //////////////////////////////////////////////////////////////////////////////////////////////
puncher.move_voltage(127);
  pros::c::delay(27000);
puncher.move_voltage(0);
  pros::delay(50);

chassis.pid_drive_set(9, DRIVE_SPEED, true);
  chassis.pid_wait(); 


//make way to other side of match load bar///////////////////////

chassis.pid_turn_set(208, TURN_SPEED);
  chassis.pid_wait();
chassis.pid_drive_set(-9, DRIVE_SPEED, true);
  chassis.pid_wait();  
chassis.pid_drive_set(-256, DRIVE_SPEED, true);
  chassis.pid_wait();


//score on left side of goal 
chassis.pid_turn_set(180,TURN_SPEED);
  chassis.pid_wait();
Vwings.set_value(true);
  chassis.pid_wait();
chassis.pid_drive_set(-40, DRIVE_SPEED, true);
  chassis.pid_wait();
Vwings.set_value(false);
  chassis.pid_wait();  
chassis.pid_drive_set(-30, DRIVE_SPEED, true);
  chassis.pid_wait();
chassis.pid_turn_set(120, DRIVE_SPEED);
  chassis.pid_wait();
chassis.pid_drive_set(-50, DRIVE_SPEED, true);
  chassis.pid_wait();
chassis.pid_drive_set(25, DRIVE_SPEED, true);
  chassis.pid_wait();
chassis.pid_drive_set(-35, DRIVE_SPEED, true);
  chassis.pid_wait();
chassis.pid_drive_set(25, DRIVE_SPEED, true);
  chassis.pid_wait();

//score left centar of goal   
chassis.pid_turn_set(40, TURN_SPEED);
  chassis.pid_wait();
 
chassis.pid_drive_set(-132, DRIVE_SPEED, true);
  chassis.pid_wait();
chassis.pid_turn_set(110, TURN_SPEED);
  chassis.pid_wait();
 chassis.pid_drive_set(-75, DRIVE_SPEED, true);
  chassis.pid_wait();

chassis.pid_turn_set(215, TURN_SPEED);
  chassis.pid_wait();
Vwings.set_value(true);
  chassis.pid_wait(); 
chassis.pid_drive_set(-102, DRIVE_SPEED, true);
  chassis.pid_wait();

Vwings.set_value(false);
  chassis.pid_wait();
chassis.pid_drive_set(80, DRIVE_SPEED, true);
  chassis.pid_wait();


//score right centar of goal 

chassis.pid_turn_set(110, TURN_SPEED);
  chassis.pid_wait();
chassis.pid_drive_set(-62, DRIVE_SPEED, true);
  chassis.pid_wait();

chassis.pid_turn_set(215, DRIVE_SPEED, true);
  chassis.pid_wait();
Vwings.set_value(true);
  chassis.pid_wait();
chassis.pid_drive_set(-102, DRIVE_SPEED, true);
  chassis.pid_wait();

Vwings.set_value(false);
  chassis.pid_wait();
chassis.pid_drive_set(35, DRIVE_SPEED, true);
  chassis.pid_wait();


//score on right side of goal
/*chassis.set_turn_pid(110, DRIVE_SPEED);
  chassis.wait_drive();
chassis.set_drive_pid(-62, DRIVE_SPEED);
  chassis.wait_drive();

chassis.set_turn_pid(215, TURN_SPEED);
  chassis.wait_drive();
chassis.set_drive_pid(-85, DRIVE_SPEED);
  chassis.wait_drive();
  */

chassis.pid_turn_set(120, TURN_SPEED);
  chassis.pid_wait();
chassis.pid_drive_set(-112, DRIVE_SPEED, true);
  chassis.pid_wait();

chassis.pid_turn_set(250, TURN_SPEED);
  chassis.pid_wait();
chassis.pid_drive_set(-100, DRIVE_SPEED, true);
  chassis.pid_wait();

chassis.pid_drive_set(50, DRIVE_SPEED, true);
  chassis.pid_wait();
chassis.pid_drive_set(-50, DRIVE_SPEED, true);
  chassis.pid_wait();
chassis.pid_drive_set(50, DRIVE_SPEED, true);
  chassis.pid_wait();

chassis.pid_turn_set(-80, TURN_SPEED);
  chassis.pid_wait();
chassis.pid_drive_set(-110, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .