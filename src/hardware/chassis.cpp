//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Chassis definitions

#include "main.h"


// Set brake modes
h_chassis& h_chassis::set_brake_mode(pros::motor_brake_mode_e brake_mode)
{
    pros::c::motor_set_brake_mode(m_pt_motor_lf, brake_mode);
    pros::c::motor_set_brake_mode(m_pt_motor_lb, brake_mode);
    pros::c::motor_set_brake_mode(m_pt_motor_rf, brake_mode);
    pros::c::motor_set_brake_mode(m_rv_motor_rb, brake_mode);
}

// Constructor
h_chassis::h_chassis
    (
        h_chassis_l pt_l, h_chassis_r pt_r,
        pros::motor_gearset_e cart, 
        pros::motor_brake_mode_e brake, 
        pros::motor_encoder_units_e enc_unit,
        bool rv_l, bool rv_r
    ) : m_pt_motor_lf {pt_l.m_motor_f}, m_pt_motor_lb {pt_l.m_motor_b}, 
        m_pt_motor_rf {pt_r.m_motor_f}, m_pt_motor_rb {pt_r.m_motor_b},
        m_rv_motor_lf {rv_l}, m_rv_motor_lb {rv_l}, 
        m_rv_motor_rf {rv_r}, m_rv_motor_rb {rv_r}
{
    // Set cartridges
    pros::c::motor_set_gearing(m_pt_motor_lf, cart);
    pros::c::motor_set_gearing(m_pt_motor_lb, cart);
    pros::c::motor_set_gearing(m_pt_motor_rf, cart);
    pros::c::motor_set_gearing(m_rv_motor_rb, cart);

    // Set break modes
    set_brake_mode(brake);

    // Set encoder units
    pros::c::motor_set_encoder_units(m_pt_motor_lf, enc_unit);
    pros::c::motor_set_encoder_units(m_pt_motor_lb, enc_unit);
    pros::c::motor_set_encoder_units(m_pt_motor_rf, enc_unit);
    pros::c::motor_set_encoder_units(m_pt_motor_rb, enc_unit);

    // Set direction
    pros::c::motor_set_reversed(m_pt_motor_lf, m_rv_motor_lf);
    pros::c::motor_set_reversed(m_pt_motor_lb, m_rv_motor_lb);
    pros::c::motor_set_reversed(m_pt_motor_rf, m_rv_motor_rf);
    pros::c::motor_set_reversed(m_pt_motor_rb, m_rv_motor_rb); 
}
