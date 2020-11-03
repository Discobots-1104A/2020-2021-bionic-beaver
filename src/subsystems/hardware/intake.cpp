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


//* Telemetry *//

/// Get the average current draw of all motors on the intake.
/// \return Average current draw to the closest milliamp.
int h_Intake::get_intake_current(void)
{
    return std::round((pros::c::motor_get_current_draw(m_motor_l) +
                       pros::c::motor_get_current_draw(m_motor_r)) / 4.0);
}

/// Get the average voltage of all motors on the intake.
/// \return Average voltage to the closest millivolt.
int h_Intake::get_intake_voltage(void)
{
    return std::round((pros::c::motor_get_voltage(m_motor_l) +
                       pros::c::motor_get_voltage(m_motor_r)) / 4.0);
}

/// Get the average power of all motors on the intake.
/// \return Average power in watts.
double h_Intake::get_intake_power(void)
{
    return ((pros::c::motor_get_power(m_motor_l) +
             pros::c::motor_get_power(m_motor_r)) / 4.0);
}

/// Get the average temperature of all motors on the intake.
/// \return Average temperature in Celcius.
double h_Intake::get_intake_temperature(void)
{
    return ((pros::c::motor_get_temperature(m_motor_l) +
             pros::c::motor_get_temperature(m_motor_r)) / 4.0);
}

/// Get the average efficiency of all motors on the intake.
/// \return Average efficiency in percentage.
double h_Intake::get_intake_efficiency(void)
{
    return ((pros::c::motor_get_efficiency(m_motor_l) +
             pros::c::motor_get_efficiency(m_motor_r)) / 4.0);
}

/// Get the current draws of each motor. 
/// In the order of: LEFT, RIGHT.
/// \return Current draws in milliamps in a 2-integer tuple.
std::tuple<int, int> h_Intake::get_current_per_motor(void)
{
    return std::make_tuple(
        pros::c::motor_get_current_draw(m_motor_l),
        pros::c::motor_get_current_draw(m_motor_r)
    );
}

/// Get the voltages of each motor. 
/// In the order of: LEFT, RIGHT.
/// \return Voltages in millivolts in a 2-integer tuple.
std::tuple<int, int> h_Intake::get_voltage_per_motor(void)
{
    return std::make_tuple(
        pros::c::motor_get_voltage(m_motor_l),
        pros::c::motor_get_voltage(m_motor_r)
    );
}

/// Get the power of each motor. 
/// In the order of: LEFT, RIGHT.
/// \return Power in watts in a 2-double tuple.
std::tuple<double, double> h_Intake::get_power_per_motor(void)
{
    return std::make_tuple(
        pros::c::motor_get_power(m_motor_l),
        pros::c::motor_get_power(m_motor_r)
    );
}

/// Get the temperatures of each motor. 
/// In the order of: LEFT, RIGHT.
/// \return Temperatures in Celcius in a 2-double tuple.
std::tuple<double, double> h_Intake::get_temperature_per_motor(void)
{
    return std::make_tuple(
        pros::c::motor_get_temperature(m_motor_l),
        pros::c::motor_get_temperature(m_motor_r)
    );
}

/// Get the efficiencies of each motor. 
/// In the order of: LEFT, RIGHT.
/// \return Efficiencies in percentages in a 2-double tuple.
std::tuple<double, double> h_Intake::get_efficiency_per_motor(void)
{
    return std::make_tuple(
        pros::c::motor_get_efficiency(m_motor_l),
        pros::c::motor_get_efficiency(m_motor_r)
    );
}

/// Get the stopped status of each motor. 
/// In the order of: LEFT, RIGHT.
/// \return A 2-boolean tuple.
std::tuple<bool, bool> h_Intake::is_stopped_per_motor(void)
{
    return std::make_tuple(
        pros::c::motor_is_stopped(m_motor_l) ? true : false,
        pros::c::motor_is_stopped(m_motor_r) ? true : false
    );
}

/// Get the over-temperature status of each motor. 
/// In the order of: LEFT, RIGHT.
/// \return A 2-boolean tuple.
std::tuple<bool, bool> h_Intake::is_over_temp_per_motor(void)
{
    return std::make_tuple(
        pros::c::motor_is_over_temp(m_motor_l) ? true : false,
        pros::c::motor_is_over_temp(m_motor_r) ? true : false
    );
}


//* Configuration *//

/// \return Intake max motor velocity in RPM.
int h_Intake::get_max_motor_velocity(void) {return m_max_motor_velocity;}

/// \return Current set brake mode.
pros::motor_brake_mode_e h_Intake::get_brake_mode(void) {return m_brake_mode;}

/// \return Current set encoder units.
pros::motor_encoder_units_e h_Intake::get_encoder_units(void) {return m_enc_unit;}

/// Sets the brake mode of the intakes.
/// \param brake_mode Supplied motor brake mode.
/// \return this* pointer for function chaining.
h_Intake& h_Intake::set_brake_mode(pros::motor_brake_mode_e brake_mode)
{
    pros::c::motor_set_brake_mode(m_motor_l, brake_mode);
    pros::c::motor_set_brake_mode(m_motor_r, brake_mode);
    m_brake_mode = brake_mode;
    return *this;
}

/// Sets the encoder units of the intakes.
/// \param enc_unit Supplied motor encoder units.
/// \return this* pointer for function chaining.
h_Intake& h_Intake::set_encoder_units(pros::motor_encoder_units_e enc_unit)
{
    pros::c::motor_set_encoder_units(m_motor_l, enc_unit);
    pros::c::motor_set_encoder_units(m_motor_r, enc_unit);
    m_enc_unit = enc_unit;
    return *this;
}
