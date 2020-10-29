//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Chassis definitions

#include "main.h"


/// Set brake modes
h_intake& h_intake::set_brake_mode(pros::motor_brake_mode_e brake_mode)
{
    pros::c::motor_set_brake_mode(m_pt_motor_l, brake_mode);
    pros::c::motor_set_brake_mode(m_pt_motor_r, brake_mode);
}

/// Constructor
h_intake::h_intake
    (
        std::uint8_t pt_motor_l,
        std::uint8_t pt_motor_r,
        pros::motor_gearset_e cart,
        pros::motor_brake_mode_e brake,
        pros::motor_encoder_units_e enc_unit,
        bool rv_l, bool rv_r
    ) : m_pt_motor_l {pt_motor_l}, m_pt_motor_r {pt_motor_r},
        m_rv_motor_l {rv_l}, m_rv_motor_r {rv_r}
{
    // Set cartridges
    pros::c::motor_set_gearing(m_pt_motor_l, cart);
    pros::c::motor_set_gearing(m_pt_motor_r, cart);

    // Set brake modes
    set_brake_mode(brake);

    // Set encoder units
    pros::c::motor_set_encoder_units(m_pt_motor_l, enc_unit);
    pros::c::motor_set_encoder_units(m_pt_motor_r, enc_unit);

    // Set direction
    pros::c::motor_set_reversed(m_pt_motor_l, m_rv_motor_l);
    pros::c::motor_set_reversed(m_pt_motor_r, m_rv_motor_r);
}

/// Move intakes, motors together, velocity
void h_intake::move_vel(int vel)
{
    pros::c::motor_move_velocity(m_pt_motor_l, vel);
    pros::c::motor_move_velocity(m_pt_motor_r, vel);
}

/// Move intakes, motors separate, velocity
void h_intake::move_vel(int vel_l, int vel_r)
{
    pros::c::motor_move_velocity(m_pt_motor_l, vel_l);
    pros::c::motor_move_velocity(m_pt_motor_r, vel_r);
}
