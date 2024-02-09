#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;

extern pros::Motor puncher;
extern pros::Motor intake;
extern pros::Controller master;
extern pros::ADIDigitalOut Hwings;
extern pros::ADIDigitalOut Vwings;
extern pros::ADIDigitalOut hang;

void Elems_sixBall();
void quals_WinPoint();
void skills();
void wait_until_change_speed();
void swing_example();
void combining_movements();
void interfered_example();

void default_constants();