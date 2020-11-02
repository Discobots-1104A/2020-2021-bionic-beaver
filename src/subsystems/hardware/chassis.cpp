//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Chassis class definitions

#include "main.h"


/// Skid steer chassis constructor. Port nums and scales must be supplied. Motor 
/// configs have default parameters. Interfaces with PROS C functions to configure 
/// each drive motor.
/// \param port_nums Supplied port numbers. Negative numbers reverse the motor.
/// \param scales Supplied chassis scales.
/// \param cart Supplied motor cartridges.
/// \param brake_mode Supplied motor brake modes.
/// \param enc_unit Supplied motor encoder units.
h_Skid_Steer_Chassis::h_Skid_Steer_Chassis
(
    h_Chassis_Port_Numbers      port_nums,
    h_Chassis_Scales            scales,
    pros::motor_gearset_e       cart,
    pros::motor_brake_mode_e    brake_mode,
    pros::motor_encoder_units_e enc_unit
)   : m_motor_lf{static_cast<std::uint8_t>(std::abs(port_nums.m_motor_lf))}, 
      m_motor_lb{static_cast<std::uint8_t>(std::abs(port_nums.m_motor_lb))},
      m_motor_rf{static_cast<std::uint8_t>(std::abs(port_nums.m_motor_rf))}, 
      m_motor_rb{static_cast<std::uint8_t>(std::abs(port_nums.m_motor_rb))},
      m_length{scales.frame_dims.m_length}, m_width{scales.frame_dims.m_width},
      m_wheel_diameter{scales.wheel_dims.m_wheel_diameter}, m_wheelbase_length{scales.wheel_dims.m_wheelbase_length},
      m_gear_ratio{scales.misc.m_gear_ratio}, m_max_motor_velocity{scales.misc.m_max_motor_velocity}, m_max_total_velocity{scales.misc.m_max_total_velocity},
      m_cart{cart}, m_brake_mode{brake_mode}, m_enc_unit{enc_unit}
{
    // Assign motor direction
    pros::c::motor_set_reversed(m_motor_lf, (port_nums.m_motor_lf < 0) ? true : false);
    pros::c::motor_set_reversed(m_motor_lb, (port_nums.m_motor_lb < 0) ? true : false);
    pros::c::motor_set_reversed(m_motor_rf, (port_nums.m_motor_rf < 0) ? true : false);
    pros::c::motor_set_reversed(m_motor_rb, (port_nums.m_motor_rb < 0) ? true : false);
}
