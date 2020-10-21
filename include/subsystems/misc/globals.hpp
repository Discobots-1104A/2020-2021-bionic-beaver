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
    inline constexpr int h_max_readtime {10};       // Max millis rate the sensors can read. //! (note that OCRs for sure at 10ms, but idk about rest)   
}

namespace k_Auto    // Autonomous constants.
{
    inline constexpr double a_def_kP {0.1};                 // Default proportional gain.
    inline constexpr double a_def_kI {0.0};                 // Default integral gain.
    inline constexpr double a_def_kD {0.5};                 // Default derivative gain.
    inline constexpr double a_def_integ_windup {0.0};       // Default integral windup threshold.
    inline constexpr int a_def_ocr_tick_range {5};          // Default OCR tick percentage of error.
    inline constexpr double a_def_imu_head_range {0.25};    // Default IMU heading percentage of error.
    inline constexpr double a_p_trn_kP {1.15};              // Point turn proportional gain.
    inline constexpr double a_p_trn_kI {0.0};               // Point turn integral gain.
    inline constexpr double a_p_trn_kD {2.5};               // Point turn derivative gain.
    inline constexpr int a_max_str_speed {175};             // Maximum speed for straight driving.
    inline constexpr int a_max_p_trn_speed {50};            // Maximum speed for point turning.
    inline constexpr int a_min_chassis_vel {15};            // Minimum motor velocity on chassis (for PID).
}

//* External objects

extern h_Intake     *h_obj_intake;      // Pointer to intake object.
extern h_Conveyor   *h_obj_conveyor;    // Pointer to conveyor object.
extern h_Chassis    *h_obj_chassis;     // Pointer to chassis object.
extern h_Sensors    *h_obj_sensors;     // Pointer to sensors object.

extern a_PID        *a_obj_pid;         // Pointer to a_PID object.
extern a_Bad_Move   *a_obj_bad_move;    // Pointer to simple movement object.

extern pros::vision_signature_s_t h_obj_red_sig;    // Red Vision signature.
extern pros::vision_signature_s_t h_obj_blu_sig;    // Blue Vision signature.

extern pros::Controller h_obj_ctrl;     // Controller object.

extern h_sVision_IDs h_sorted_ball_id;  // Ball sort ID.

extern a_Autonomous_Routine a_routine;  // Autonomous routine ID.

#endif  // HARDWARE_HPP
