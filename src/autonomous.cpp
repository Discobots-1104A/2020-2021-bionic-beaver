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

// This is an autonomous macro which scores the alliance ball before descoring the opponent balls. 
// The first while loop aims to score the alliance ball into the tower. 
// The second while loop aims to descore the opponent balls from the tower. If we 
// detect that we sucked the red ball back in, score it back in from the top again.
void score_and_descore()
{
    while (true)
    {
        pros::vision_object_s_t ball {h_obj_sensors->get_obj_sig(0, h_sVision_IDs::RED_ID)};
        if (ball.width < 50)
        {
            pros::delay(2000);
            break;
        }
        
        h_obj_conveyor->set_vel(600);
        pros::delay(k_Hardware::h_max_readtime);
    }

    while (true)
    {
        pros::vision_object_s_t ball {h_obj_sensors->get_obj_siz(0)};
        if (ball.signature == static_cast<int>(h_sVision_IDs::RED_ID) && ball.width > 50)
        {
            h_obj_intake->set_vel();
            break;
        }

        h_obj_conveyor->set_vel((ball.width > 50) ? -600 : 600, 600);
        h_obj_intake->set_vel(600);
        pros::delay(k_Hardware::h_max_readtime);
    }

    while (true)
    {
        pros::vision_object_s_t ball {h_obj_sensors->get_obj_sig(0, h_sVision_IDs::RED_ID)};
        if (ball.width < 50)
        {
            pros::delay(3000);
            h_obj_conveyor->set_vel();
            break;
        }
        
        h_obj_conveyor->set_vel(600);
        pros::delay(k_Hardware::h_max_readtime);
    }
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
    //--START OF SECTION ONE--//
    // This part just scores the preload ball into Goal I.
    // It immediately grants us 19 points:
    //   - 3 descored rows * 6.
    //   - 1 alliance ball scored.

    // Reset the encoders.
    h_obj_sensors->reset_enc();

    // Score the preload ball in.
    // The use of the Vision sensor is to make sure that the ball does go in.
    while (true)
    {
        pros::vision_object_s_t ball {h_obj_sensors->get_obj_sig(0, h_sVision_IDs::RED_ID)};
        if (ball.width > 200)
        {
            pros::delay(2000);
            h_obj_conveyor->set_vel();
            break;
        }

        h_obj_conveyor->set_vel(600);
        pros::delay(k_Hardware::h_max_readtime);
    }

    // Back out by a foot or so.
    a_obj_pid->set_target(a_Ticks{1.0_ft}).drive();
    pros::delay(50);

    // Turn to 90 degrees heading relative to our starting position
    a_obj_pid->set_gains(gains_p_trn).set_target(a_Degrees{90.0}).drive();
    pros::delay(50);

#if defined SECTION_ONE
    return;
#endif
    //---END OF SECTION ONE---//

    //--START OF SECTION TWO--//

#if defined SECTION_TWO
    return;
#endif
    //---END OF SECTION TWO---//

    //--START OF SECTION THREE--//

#if defined SECTION_THREE
    return;
#endif
    //---END OF SECTION THREE---//
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
