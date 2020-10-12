//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Main autonomous control code.


//* Headers
#include "main.h"   // Main header.


//* Local "global" variables
a_PID pid{a_PID_Gains{0.1, 0, 0.5, 5, 0, 2, 0.25}};

//* Functions

// Main autonomous control callback.
void autonomous()
{
    h_obj_sensors.reset();
    pid.reset().set_target(a_Ticks{720}).drive();
    pros::delay(1000);
    pid.set_target(a_Ticks{-720}).drive();
    pros::delay(2000);
    pid.set_target(a_Degrees{90}).drive();
    pros::delay(1000);
    pid.set_target(a_Degrees{0}).drive();
    pros::delay(1000);
    pid.set_target(a_Degrees{270}).drive();
    pros::delay(1000);
    pid.set_target(a_Degrees{0}).drive();
}
