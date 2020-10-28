//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Chassis declarations.

//! Try to prefix the main declarations with "h_"

#ifndef CHASSIS_HPP
#define CHASSIS_HPP

#include "api.h"

/// Left side chassis motors
struct h_chassis_l
{
    std::uint8_t m_motor_f;
    std::uint8_t m_motor_b;
};

/// Right side chassis motors
struct h_chassis_r
{
    std::uint8_t m_motor_f;
    std::uint8_t m_motor_b;
};

/// Chassis control class
class h_chassis
{
public:
    // Constructor
    h_chassis(
        h_chassis_l pt_l, h_chassis_r pt_r,
        pros::motor_gearset_e cart = pros::E_MOTOR_GEARSET_18, 
        pros::motor_brake_mode_e brake = pros::E_MOTOR_BRAKE_COAST, 
        pros::motor_encoder_units_e enc_unit = pros::E_MOTOR_ENCODER_COUNTS,
        bool rv_l = false, bool rv_r = true
    );

    // Movement
    void move(int vol);
    void move(int vol_l, int vol_r);
    void move_vel(int vel);
    void move_vel(int vel_l, int vel_r);

    // Config
    h_chassis& set_brake_mode(pros::motor_brake_mode_e brake_mode);


private:
    // Port numbers
    std::uint8_t    m_pt_motor_lf,
                    m_pt_motor_lb,
                    m_pt_motor_rf,
                    m_pt_motor_rb;

    // Motor is reversed
    bool    m_rv_motor_lf,
            m_rv_motor_lb,
            m_rv_motor_rf,
            m_rv_motor_rb;

    // Gearset
    pros::motor_gearset_e m_cart;

    // Brake mode
    pros::motor_brake_mode_e m_brake;

    // Encoder units
    pros::motor_encoder_units_e m_enc_unit;
};

#endif  // CHASSIS_HPP
