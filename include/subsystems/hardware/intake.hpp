//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-29
//* Desc: Intake class declarations.

//! Prefix all objects here with "h_" except for child members and namespaces.

#ifndef H_INTAKE_HPP
#define H_INTAKE_HPP

//* Headers
#include "api.h"


//* User-defined types

/// struct - Intake ports.
//? In order of: left, right.
struct h_Intake_Ports
{
    std::uint8_t pt_IL;     // Intake port, left.
    std::uint8_t pt_IR;     // Intake port, right.
};

/// class - Intake
/// Has all the necessary objects and functions.
class h_Intake
{
public:
    h_Intake(
        const h_Intake_Ports &ports,
        pros::motor_gearset_e cartridge = pros::E_MOTOR_GEARSET_06,
        pros::motor_encoder_units_e enc_unit = pros::E_MOTOR_ENCODER_COUNTS,
        pros::motor_brake_mode_e brake_mode = pros::E_MOTOR_BRAKE_HOLD
    );
    h_Intake& set_brake_mode(pros::motor_brake_mode_e brake_mode);
    h_Intake& set_brake_mode(pros::motor_brake_mode_e brake_mode_l, pros::motor_brake_mode_e brake_mode_r);
    h_Intake& reset_enc();
    void set_vel(int velocity = 0);
    void set_vel(int l_velocity, int r_velocity);
    void set_abs(double position, int velocity);

private:
    pros::Motor m_IL;
    pros::Motor m_IR;

};

#endif  // H_INTAKE_HPP
