//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Main autonomous control code.


//* Headers
#include "main.h"   // Main header.


//* Local "global" variables
a_PID* pid = new a_PID{a_PID_Gains{0.1, 0, 0.5, 5, 0, 2, 0.25}};
a_Bad_Move* bad_move = new a_Bad_Move{};

//* Functions

// Main autonomous control callback.
void autonomous()
{
    pid->reset();
    pid->set_target(a_Ticks{720}).drive();
    pros::delay(1000);
    pid->set_target(a_Ticks{-720}).drive();
    pros::delay(1000);
}
