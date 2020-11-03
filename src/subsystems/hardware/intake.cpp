//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Intake class definitions

#include "main.h"


//* Constructor and destructor *//

/// Intake constructor. Port nums and scales must be supplied. Motor 
/// configs have default parameters. Interfaces with PROS C functions to configure 
/// each drive motor.
/// \param port_nums Supplied port numbers. Negative numbers reverse the motor.
/// \param scales Supplied conveyor scales.
/// \param cart Supplied motor cartridges.
/// \param brake_mode Supplied motor brake mode.
/// \param enc_unit Supplied motor encoder units.
h_Intake::h_Intake
(
    h_Intake_Port_Numbers       port_nums,
    h_Intake_Scales             scales,
    pros::motor_gearset_e       cart            = pros::E_MOTOR_GEARSET_06,
    pros::motor_brake_mode_e    brake_mode      = pros::E_MOTOR_BRAKE_HOLD,
    pros::motor_encoder_units_e enc_unit        = pros::E_MOTOR_ENCODER_COUNTS
)   : m_motor_l{static_cast<std::uint8_t>(std::abs(port_nums.m_motor_l))},
      m_motor_r{static_cast<std::uint8_t>(std::abs(port_nums.m_motor_r))},
      m_max_motor_velocity{scales.m_max_motor_velocity},
      m_cart{cart}, m_brake_mode{brake_mode}, m_enc_unit{enc_unit}
{
    // Assign motor direction
    pros::c::motor_set_reversed(m_motor_l, (port_nums.m_motor_l > 0) ? true : false);
    pros::c::motor_set_reversed(m_motor_r, (port_nums.m_motor_r > 0) ? true : false);

    // Assign motor cartridges
    pros::c::motor_set_gearing(m_motor_l, m_cart);
    pros::c::motor_set_gearing(m_motor_r, m_cart);

    // Assign brake modes
    set_brake_mode(m_brake_mode);

    // Assign encoder units
    set_encoder_units(m_enc_unit);
}


//* Movement *//

/// Moves the intake motors together.
/// \param vel Velocity in RPM within the range of the previously supplied cartridge.
void h_Intake::move_vel(int vel)
{
    pros::c::motor_move_velocity(m_motor_l, vel);
    pros::c::motor_move_velocity(m_motor_r, vel);
}

/// Moves the intake motors separately.
/// \param vel_l Left velocity in RPM within the range of the previously supplied cartridge.
/// \param vel_r Right velocity in RPM within the range of the previously supplied cartridge.
void h_Intake::move_vel(int vel_l, int vel_r)
{
    pros::c::motor_move_velocity(m_motor_l, vel_l);
    pros::c::motor_move_velocity(m_motor_r, vel_r);
}
