//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-10-13
//* Desc: mfw pid controller no work.
//*       Temporary movement code that's very bad. Definitions


//* Headers
#include "main.h"   // Main header.


//* Definitions

/// Constructor. Does nothing ATM.
a_Bad_Move::a_Bad_Move()
{}

/// Move in a straight line.
/// \param dist Distance to move to.
void a_Bad_Move::move_str(double dist)
{
    // Set a fixed speed based on the direction of the target.
    h_obj_chassis->drive_vel(std::copysign(50, dist));

    // Loop until OCRs tell us that we've reach the target.
    while (std::fabs(dist - h_obj_sensors->get_enc(h_Encoder_IDs::AVG_SIDES)) > k_Auto::a_def_ocr_tick_range)
    {
        // Delay because the OCRs can't read any faster than this.
        pros::delay(k_Hardware::h_max_readtime);
    }

    // Stop the motors.
    h_obj_chassis->drive_vel();

    // Reset OCR values.
    h_obj_sensors->reset_enc();
}

/// Point turn around center of robot.
/// \param head Heading to move to.
void a_Bad_Move::move_pnt_trn(double head)
{
    // Calculate the shortest angle towards the target from current heading.
    double diff { fmod( (head - h_obj_sensors->get_heading() + 180.0), 360.0) - 180 };
    double theta { ( (diff < -180) ? diff + 360 : diff ) };

    // Set a fixed speed based on the shortest angle to the target from current heading.
    h_obj_chassis->drive_vel(std::copysign(50, theta), std::copysign(50, -theta));

    // Loop until IMU tells us that we've reached the target.
    while (std::fabs(head - h_obj_sensors->get_heading()) > k_Auto::a_def_imu_head_range)
    {
        // Delay because the IMU can't read any faster than this.
        pros::delay(k_Hardware::h_max_readtime);
    }

    // Stop the motors.
    h_obj_chassis->drive_vel();

    // Reset OCR values.
    h_obj_sensors->reset_enc();
}
