//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Conveyor class definitions

#include "main.h"


//* Constructor and destructor *//

/// Conveyor constructor. Port nums and scales must be supplied. Motor 
/// configs have default parameters. Interfaces with PROS C functions to configure 
/// each drive motor.
/// \param port_nums Supplied port numbers. Negative numbers reverse the motor.
/// \param scales Supplied conveyor scales.
/// \param cart Supplied motor cartridges.
/// \param brake_mode_t Supplied top motor brake mode.
/// \param brake_mode_b Supplied bottom motor brake mode.
/// \param enc_unit Supplied motor encoder units.
h_Conveyor::h_Conveyor
(
    h_Conveyor_Port_Numbers     port_nums,
    h_Conveyor_Scales           scales,
    pros::motor_gearset_e       cart,
    pros::motor_brake_mode_e    brake_mode_t,
    pros::motor_brake_mode_e    brake_mode_b,
    pros::motor_encoder_units_e enc_unit
)   : m_motor_t{static_cast<std::uint8_t>(std::abs(port_nums.m_motor_t))},
      m_motor_b{static_cast<std::uint8_t>(std::abs(port_nums.m_motor_b))},
      m_max_motor_velocity{scales.m_max_motor_velocity},
      m_max_top_roller_velocity{scales.m_max_top_roller_velocity},
      m_cart{cart}, m_brake_mode_t{brake_mode_t}, m_brake_mode_b{brake_mode_b}, m_enc_unit{enc_unit}
{
    // Assign motor direction
    pros::c::motor_set_reversed(m_motor_t, (port_nums.m_motor_t > 0) ? true : false);
    pros::c::motor_set_reversed(m_motor_b, (port_nums.m_motor_b > 0) ? true : false);

    // Assign motor cartridges
    pros::c::motor_set_gearing(m_motor_t, m_cart);
    pros::c::motor_set_gearing(m_motor_b, m_cart);

    // Assign brake modes
    set_brake_mode(m_brake_mode_t, m_brake_mode_b);

    // Assign encoder units
    set_encoder_units(m_enc_unit);
}



//* Movement *//


//* Telemetry *//


//* Configuration *//
