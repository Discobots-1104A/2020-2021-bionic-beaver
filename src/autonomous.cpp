//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Main autonomous control code.


//* Headers
#include "main.h"   // Main header.


//* Functions

// Red routine.
void red()
{
    
}

// Blue routine.
void blue()
{

}

// Skills routine.
void skills()
{
    a_obj_pid->reset();
    a_obj_pid->set_target(a_Ticks{1440}).drive();
    pros::delay(1000);
    a_obj_pid->set_target(a_Ticks{-1440}).drive();
    pros::delay(1000);
}

// Main autonomous control callback.
void autonomous()
{
    // Create new a_PID object into heap memory.
    a_obj_pid = new a_PID{a_PID_Gains{
        k_Auto::a_def_kP, k_Auto::a_def_kI, k_Auto::a_def_kD, 
        k_Hardware::h_max_readtime, k_Auto::a_def_integ_windup, 
        k_Auto::a_def_ocr_tick_range, k_Auto::a_def_imu_head_range}};
    
    // Run each auto routine based on selected auto.
    switch (a_routine)
    {
    case a_Autonomous_Routine::RED:
        red();
        break;
    case a_Autonomous_Routine::BLUE:
        blue();
        break;
    case a_Autonomous_Routine::SKILLS:
        skills();
        break;
    }
}
