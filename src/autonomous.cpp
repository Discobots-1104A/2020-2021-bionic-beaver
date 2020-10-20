//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Main autonomous control code.


//* Headers
#include "main.h"   // Main header.


//* Defines for testing purposes.
#define SECTION_ONE

//* Local "global" objects.

// PID gains for straight movements.
a_PID_Gains gains_str {
    k_Auto::a_def_kP, k_Auto::a_def_kI, k_Auto::a_def_kD, 
    k_Hardware::h_max_readtime, k_Auto::a_def_integ_windup, 
    k_Auto::a_def_ocr_tick_range, k_Auto::a_def_imu_head_range};

// PID gains for point turns.
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
    // --BEGINNING OF SECTION ONE--
    // This section moves the robot from the starting position, intakes the ball immediately 
    // before it, then turns around to the corner goal and shoots a ball into it.
    // This grants us 19 points immediately through 3 descored rows + 1 alliance ball.

    // Reset sensors.
    h_obj_sensors->reset();

    // Flip the hood out.
    h_obj_conveyor->set_vel(600, 0);
    pros::delay(250);
    h_obj_conveyor->set_vel();
    
    // Start the intakes, drive straight forward for about 3 feet (1269 OCR encoder ticks).
    // The conveyor code is to make sure the alliance ball is in the correct position.
    h_obj_conveyor->set_abs(0, 600, 0, 600);
    h_obj_intake->set_vel(600);
    a_obj_pid->set_target(a_Ticks{1269}).drive();
    pros::delay(100);
    h_obj_conveyor->reset_enc();
    h_obj_intake->set_vel();

    // Turn -145 degrees relative to our starting position, then go forward for about 3 feet as well.
    // This gets the robot in front of the corner goal.
    a_obj_pid->set_gains(gains_p_trn).set_target(a_Degrees{215.0}).drive();
    pros::delay(100);
    a_obj_pid->set_gains(gains_str).set_target(a_Ticks{1220}).drive();
    pros::delay(100);

    // Score the ball into the tower.
    h_obj_conveyor->set_vel(600);
    pros::delay(1000);
    h_obj_conveyor->set_vel();

    // Then back out about one foot.
    a_obj_pid->set_target(a_Ticks{-423}).drive();
    pros::delay(100);
#if defined SECTION_ONE
    return;
#endif
    // --END OF SECTION ONE--

    // --BEGINNING OF SECTION TWO--
    // This section moves the robot towards the alliance ball nearest to the tangent of the center 
    // tower, of which is parallel to our starting side. The robot then intakes the ball, drives 
    // up to the tower, and scores the ball in, descoring a minimum of 1 opponent balls.
    // This bumps our score up to 39; 3 more descored rows, 1 more alliance ball, and a minimum of 1
    // opponent ball descored. If all 3 opponent balls are descored, it's bumped up to 42 points instead.

    // Turn -152 degrees relative to our starting position.
    a_obj_pid->set_gains(gains_p_trn).set_target(a_Degrees{063.0}).drive();
    pros::delay(100);

    // Start the intakes and drive 2 * sqrt(5) ft (about 4.47) towards the ball, intaking it.
    h_obj_intake->set_vel(600);
    a_obj_pid->set_gains(gains_str).set_target(a_Ticks{1892}).drive();
    h_obj_conveyor->set_abs(0, 600, 0, 600);
    pros::delay(500);
    h_obj_conveyor->reset_enc();
    h_obj_intake->set_vel();

    // Return to our home heading that was set during initialization.
    a_obj_pid->set_gains(gains_p_trn).set_target(a_Degrees{360.0}).drive();
    pros::delay(100);

    // Drive into the middle tower (about a foot). The intakes are turned on to 
    // assist with the posts on the middle tower. 
    h_obj_intake->set_vel(600);
    a_obj_pid->set_gains(gains_str).set_target(a_Ticks{423}).drive();

    // And then score the alliance ball into the tower. Vision sensor is used to automatically 
    // sort the balls here.
    for (auto i {0}; i < 1000; i += 10)
    {
        pros::vision_object_s_t ball {h_obj_sensors->get_obj_sig(0, h_sorted_ball_id)};
        h_obj_conveyor->set_vel(a_ball_sort(ball, 600), 600);
        pros::delay(10);
    }
    h_obj_conveyor->set_vel();
    h_obj_intake->set_vel();
    pros::delay(100);

    // Back out a foot. Reverse the intakes to help with the posts.
    h_obj_intake->set_vel(-600);
    a_obj_pid->set_target(a_Ticks{-423}).drive();
    h_obj_intake->set_vel();
    pros::delay(100);
#if defined SECTION_TWO
    return;
#endif
    // --END OF SECTION TWO--

    // --BEGINNING OF SECTION THREE--
    // This final section navigates the robot towards the opposing corner tower (relative to the
    // one that was descored in section one). We suck in the closest ball to us as we travel to the 
    // tower, and then score the ball into the tower.
    // This bumps our score up to a final of 58, up to a maximum of 60 depending on how many
    // balls were descored from the center.
    // 8 descored rows + 1 scored row + 3 alliance balls + 1-3 descored opponent balls.

    // Turn 45 degrees.
    a_obj_pid->set_gains(gains_p_trn).set_target(a_Degrees{045.0}).drive();
    pros::delay(100);

    // Start the intakes and begin driving 4 * sqrt(2) ft (about 5.66).
    h_obj_intake->set_vel(600);
    a_obj_pid->set_gains(gains_str).set_target(a_Ticks{2393}).drive();
    pros::delay(100);
    h_obj_intake->set_vel();

    // Return to our home heading that was set during initialization.
    a_obj_pid->set_gains(gains_p_trn).set_target(a_Degrees{360.0}).drive();
    pros::delay(100);

    // Drive forward for about 2 feet.
    a_obj_pid->set_gains(gains_str).set_target(a_Ticks{846}).drive();
    pros::delay(100);

    // Turn 45 degrees, then go forward for about 2 - 3 feet ish.
    a_obj_pid->set_gains(gains_p_trn).set_target(a_Degrees{045.0}).drive();
    pros::delay(100);
    a_obj_pid->set_gains(gains_str).set_target(a_Ticks{1021}).drive();
    pros::delay(100);

    // Score the ball into the tower.
    h_obj_conveyor->set_vel(600);
    pros::delay(500);
    h_obj_conveyor->set_vel();

    // Back out 1 foot. This is our final movement.
    a_obj_pid->set_target(a_Ticks{-423}).drive();
    pros::delay(100);
    // --END OF SECTION THREE--
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
