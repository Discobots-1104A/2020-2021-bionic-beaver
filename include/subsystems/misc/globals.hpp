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

//* User-defined types

/// enum - Autonomous routine.
enum a_Autonomous_Routine
{
    RED,
    BLUE,
    SKILLS
};

//* Constants
namespace k_Hardware    // Hardware constants.
{
    inline constexpr int h_mot_pos_range {5};       // Motor positional movement range.
    inline constexpr double h_tw_len {12.0};        // Tracking wheel wheelbase length.
    inline constexpr double h_tw_dia {3.25};        // Tracking wheel diameter.
    inline constexpr int h_deadzone {10};           // Deadzone value.
    inline constexpr int h_rev_top {-600};          // For ball sorting later.
    inline constexpr int h_llemu_lines {7};         // Max lines on LLEMU screen.
    inline constexpr int h_max_chassis_vel {200};   // Max motor velocity on chassis.
    inline constexpr int h_min_chassis_vel {20};    // Min motor velocity on chassis (for PID).
    inline constexpr int h_max_readtime {10};       // Max millis rate the sensors can read. //! (note that OCRs for sure at 10ms, but idk about rest)   
}

namespace k_Auto    // Autonomous constants.
{
    inline constexpr double a_def_kP {0.1};                 // Default proportional gain.
    inline constexpr double a_def_kI {0.0};                 // Default integral gain.
    inline constexpr double a_def_kD {0.5};                 // Default derivative gain.
    inline constexpr double a_def_integ_windup {0.0};       // Default integral windup threshold.
    inline constexpr double a_def_ocr_tick_range {2.0};     // Default OCR tick percentage of error.
    inline constexpr double a_def_imu_head_range {0.25};    // Default IMU heading percentage of error.
}

//* External objects

extern h_Intake*     h_obj_intake;      // Object for intakes.
extern h_Conveyor*   h_obj_conveyor;    // Object for conveyor.
extern h_Chassis*    h_obj_chassis;     // Object for chassis.
extern h_Sensors*    h_obj_sensors;     // Object for sensors

extern a_PID*       a_obj_pid;          // Object for PID.
extern a_Bad_Move*  a_obj_bad_move;     // Objecr for simple movement.

extern pros::vision_signature_s_t h_obj_red_sig;    // Red Vision signature.
extern pros::vision_signature_s_t h_obj_blu_sig;    // Blue Vision signature.

extern pros::Controller h_obj_ctrl;     // Controller object.

extern h_sVision_IDs h_sorted_ball_id;  // Ball sort ID.

extern a_Autonomous_Routine a_routine;  // Autonomous routine.

#endif  // HARDWARE_HPP
