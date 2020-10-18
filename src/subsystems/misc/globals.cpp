//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Hardware declarations.

//! Prefix all objects here with "h_" except for child members and namespaces.

//*Headers
#include "main.h"

//* External objects

h_Intake    *h_obj_intake;      // Pointer to intake object.
h_Conveyor  *h_obj_conveyor;    // Pointer to conveyor object.
h_Chassis   *h_obj_chassis;     // Pointer to chassis object.
h_Sensors   *h_obj_sensors;     // Pointer to sensors object.

a_PID       *a_obj_pid;         // Pointer to a_PID object.
a_Bad_Move  *a_obj_bad_move;    // Pointer to simple movement object.

pros::vision_signature_s_t h_obj_red_sig    // Red Vision signature.
{
    pros::Vision::signature_from_utility
    (
        static_cast<std::int32_t>(h_sVision_IDs::RED_ID),
        4229, 8837, 6533, -353, 1073, 3360, 1.5, 0
    )
};

pros::vision_signature_s_t h_obj_blu_sig    // Blue Vision signature.
{
    pros::Vision::signature_from_utility
    (
        static_cast<std::int32_t>(h_sVision_IDs::BLUE_ID),
        -2993, -1993, -2494, 9025, 13265, 11146, 1.5, 0
    )
};

pros::Controller h_obj_ctrl {pros::controller_id_e_t::E_CONTROLLER_MASTER}; // Controller object.

h_sVision_IDs h_sorted_ball_id;     // Ball sort ID.

a_Autonomous_Routine a_routine;     // Autonomous routine ID.
