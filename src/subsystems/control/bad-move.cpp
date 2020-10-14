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
    h_obj_chassis->drive_vel(std::copysign(50, dist));

    while (std::fabs(dist - h_obj_sensors->get_enc(h_Encoder_IDs::AVG_SIDES)) > 5)
    {
        pros::delay(5);
    }

    h_obj_chassis->drive_vel();
    h_obj_sensors->reset();
}

/// Point turn around center of robot.
/// \param head Heading to move to.
void a_Bad_Move::move_pnt_trn(double head)
{
    double arc {6 * (head * (M_PI / 180))};
    double rev {arc / (3.25 * M_PI)};
    double tic {std::round(360 * rev)};

    h_obj_chassis->drive_vel(std::copysign(50, tic), std::copysign(50, -tic));
    while (std::fabs(tic - h_obj_sensors->get_enc(h_Encoder_IDs::LEFT)) > 5)
    {
        pros::delay(5);
    }

    h_obj_chassis->drive_vel();
    h_obj_sensors->reset();
}
