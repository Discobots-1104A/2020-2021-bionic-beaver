//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Intake declarations.

//! Try to prefix the main declarations with "h_"

#ifndef INTAKE_HPP
#define INTAKE_HPP

#include "api.h"

/// Intake control class
class h_intake
{
public:
    h_intake(
        std::uint8_t pt_motor_l,
        std::uint8_t pt_motor_r,
        pros::motor_gearset_e cart = pros::E_MOTOR_GEARSET_06, 
        pros::motor_brake_mode_e brake = pros::E_MOTOR_BRAKE_HOLD, 
        pros::motor_encoder_units_e enc_unit = pros::E_MOTOR_ENCODER_COUNTS,
        bool rv_l = false, bool rv_r = true
    );

    // Movement
    void move_vel(int vel);
    void move_vel(int vel_l, int vel_r);

    // Config
    h_intake& set_brake_mode(pros::motor_brake_mode_e brake_mode);

private:
    // Port numbers
    std::uint8_t    m_pt_motor_l,
                    m_pt_motor_r;

    // Motor is reversed
    bool    m_pt_motor_l,
            m_pt_motor_r;

    // Gearset
    pros::motor_gearset_e m_cart;

    // Brake mode
    pros::motor_brake_mode_e m_brake;

    // Encoder units
    pros::motor_encoder_units_e m_enc_unit;
};

#endif  // INTAKE_HPP
