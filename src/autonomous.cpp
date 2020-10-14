//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Main autonomous control code.


//* Headers
#include "main.h"   // Main header.


//* Functions

// Main autonomous control callback.
void autonomous()
{
    a_obj_pid = new a_PID{a_PID_Gains{0.1, 0, 0.5, 5, 0, 2, 0.25}};
    a_obj_bad_move = new a_Bad_Move{};

    a_obj_pid->reset();
    a_obj_pid->set_target(a_Ticks{720}).drive();
    pros::delay(1000);
    a_obj_pid->set_target(a_Ticks{-720}).drive();
    pros::delay(1000);
}
