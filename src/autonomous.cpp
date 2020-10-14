//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Main autonomous control code.


//* Headers
#include "main.h"   // Main header.


//* Local "global" variables
a_Bad_Move* chungus = new a_Bad_Move{};

//* Functions

// Main autonomous control callback.
void autonomous()
{
    h_obj_sensors->reset();
    h_obj_chassis->set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    chungus->move_str(720);
    pros::delay(1000);
    chungus->move_str(-720);
    pros::delay(1000);
    chungus->move_pnt_trn(90);
    pros::delay(1000);
    chungus->move_pnt_trn(-90);
    pros::delay(1000);
    chungus->move_pnt_trn(-90);
    pros::delay(1000);
    chungus->move_pnt_trn(90);
}
