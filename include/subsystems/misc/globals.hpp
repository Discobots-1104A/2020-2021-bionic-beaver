//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Hardware declarations.

#ifndef HARDWARE_HPP
#define HARDWARE_HPP

//* Headers
#include "api.h"

//* Type aliases
using h_ctrl_analog = pros::controller_analog_e_t;
using h_ctrl_digital = pros::controller_digital_e_t;

//* Constants
namespace k_Hardware
{
    inline constexpr int h_mot_pos_range {5};       // Motor positional movement range.
    inline constexpr double h_tw_len {12.0};        // Tracking wheel wheelbase length.
    inline constexpr double h_tw_dia {3.25};        // Tracking wheel diameter.       
}

//* External objects

extern h_Intake*     h_obj_intake;       // Object for intakes.
extern h_Conveyor*   h_obj_conveyor;     // Object for conveyor.
extern h_Chassis*    h_obj_chassis;      // Object for chassis.
extern h_Sensors*    h_obj_sensors;      // Object for sensors

extern a_PID*       a_obj_pid;
extern a_Bad_Move*  a_obj_bad_move;

extern pros::vision_signature_s_t h_obj_red_sig;    // Red Vision signature.
extern pros::vision_signature_s_t h_obj_blu_sig;    // Blue Vision signature.

extern pros::Controller h_obj_ctrl;

extern h_sVision_IDs h_sorted_ball_id;

#endif  // HARDWARE_HPP
