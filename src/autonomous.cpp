//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Main autonomous control code.


//* Headers
#include "main.h"   // Main header.


//* Local "global" objects.

a_PID_Gains gains_str {
    k_Auto::a_def_kP, k_Auto::a_def_kI, k_Auto::a_def_kD, 
    k_Hardware::h_max_readtime, k_Auto::a_def_integ_windup, 
    k_Auto::a_def_ocr_tick_range, k_Auto::a_def_imu_head_range};

a_PID_Gains gains_p_trn {
    k_Auto::a_p_trn_kP, k_Auto::a_p_trn_kI, k_Auto::a_p_trn_kD, 
    k_Hardware::h_max_readtime, k_Auto::a_def_integ_windup, 
    k_Auto::a_def_ocr_tick_range, k_Auto::a_def_imu_head_range
};

//* Functions

/// Ball sorting function. Determines whether it should reverse the top roller or 
/// not to eject a ball.
/// \param ball The ball of the given sorted signature.
/// \param top_pow The default power of the top roller.
/// \return The top value or the reversing value depending on the size of the object.
int a_ball_sort(pros::vision_object_s_t &ball, int top_pow)
{
    return ((ball.width > 50) ? k_Hardware::h_rev_top : top_pow);
}

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
    h_obj_sensors->reset();
    h_obj_conveyor->set_vel(600, 0);
    pros::delay(250);
    h_obj_conveyor->set_vel();
    h_obj_intake->set_vel(600);
    a_obj_pid->set_target(a_Ticks{1269}).drive();
    pros::delay(100);
    h_obj_intake->set_vel();
    a_obj_pid->set_gains(gains_p_trn).set_target(a_Degrees{215.0}).drive();
    pros::delay(100);
    a_obj_pid->set_gains(gains_str).set_target(a_Ticks{1220}).drive();
    pros::delay(100);
    h_obj_conveyor->set_vel(600);
    h_obj_intake->set_vel(600);
    pros::delay(1000);
    h_obj_conveyor->set_vel();
    h_obj_intake->set_vel();
    a_obj_pid->set_target(a_Ticks{-423}).drive();
    pros::delay(100);

    /*
    a_obj_pid->set_gains(gains_p_trn).set_target(a_Degrees{063.0}).drive();
    pros::delay(100);
    h_obj_intake->set_vel(600);
    a_obj_pid->set_gains(gains_str).set_target(a_Ticks{4.4721_ft}).drive();
    pros::delay(100);
    h_obj_intake->set_vel();
    a_obj_pid->set_gains(gains_p_trn).set_target(a_Degrees{360.0}).drive();
    pros::delay(100);
    h_obj_intake->set_vel(600);
    a_obj_pid->set_gains(gains_str).set_target(a_Ticks{1.0_ft}).drive();
    for (auto i {0}; i < 1000; i += 10)
    {
        pros::vision_object_s_t ball {h_obj_sensors->get_obj_sig(0, h_sorted_ball_id)};
        h_obj_conveyor->set_vel(a_ball_sort(ball, 600), 600);
        pros::delay(10);
    }
    h_obj_conveyor->set_vel();
    h_obj_intake->set_vel();
    pros::delay(100);
    h_obj_intake->set_vel(-600);
    a_obj_pid->set_target(a_Ticks{-1.0_ft}).drive();
    h_obj_intake->set_vel();
    pros::delay(100);

    a_obj_pid->set_gains(gains_p_trn).set_target(a_Degrees{045.0}).drive();
    pros::delay(100);
    h_obj_intake->set_vel(600);
    a_obj_pid->set_gains(gains_str).set_target(a_Ticks{5.6569_ft}).drive();
    pros::delay(100);
    h_obj_intake->set_vel();
    a_obj_pid->set_gains(gains_p_trn).set_target(a_Degrees{360.0}).drive();
    pros::delay(100);
    a_obj_pid->set_gains(gains_str).set_target(a_Ticks{2.0_ft}).drive();
    pros::delay(100);
    a_obj_pid->set_gains(gains_p_trn).set_target(a_Degrees{045.0}).drive();
    pros::delay(100);
    a_obj_pid->set_gains(gains_str).set_target(a_Ticks{3.8284_ft}).drive();
    pros::delay(100);
    h_obj_conveyor->set_vel(600);
    pros::delay(500);
    h_obj_conveyor->set_vel();
    a_obj_pid->set_target(a_Ticks{-1.0_ft}).drive();
    pros::delay(100);
    */
}

// Main autonomous control callback.
void autonomous()
{
    // Create new a_PID object into heap memory.
    a_obj_pid = new a_PID{gains_str};
    
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
