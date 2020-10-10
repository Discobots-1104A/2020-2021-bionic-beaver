//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-29
//* Desc: Conveyor class declarations.

//! Prefix all objects here with "h_" except for child members and namespaces.

#ifndef H_CONVEYOR_HPP
#define H_CONVEYOR_HPP

//* Headers
#include "api.h"


//* User-defined types

/// struct - Conveyor ports.
//? In order of: bottom, top.
struct h_Conveyor_Ports
{
    std::uint8_t pt_CB;     // Conveyor port, bottom.
    std::uint8_t pt_CT;     // Conveyor port, top.
};

/// class - Conveyor.
/// Has all the necessary objects and functions.
class h_Conveyor
{
public:
    h_Conveyor(
        const h_Conveyor_Ports &ports,
        pros::motor_gearset_e cartridge = pros::E_MOTOR_GEARSET_06,
        pros::motor_encoder_units_e enc_unit = pros::E_MOTOR_ENCODER_COUNTS,
        pros::motor_brake_mode_e brake_mode_cb = pros::E_MOTOR_BRAKE_BRAKE,
        pros::motor_brake_mode_e brake_mode_ct = pros::E_MOTOR_BRAKE_HOLD
    );
    h_Conveyor& set_brake_mode(pros::motor_brake_mode_e brake_mode);
    h_Conveyor& set_brake_mode(pros::motor_brake_mode_e brake_mode_cb, pros::motor_brake_mode_e brake_mode_ct);
    void set_vel(int velocity = 0);
    void set_vel(int t_velocity, int b_velocity);

private:
    pros::Motor m_CB;
    pros::Motor m_CT;

};

#endif  // H_CONVEYOR_HPP
