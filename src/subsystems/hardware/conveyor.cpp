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

/// Moves the conveyor motors together.
/// \param vel Velocity in RPM within the range of the previously supplied cartridge.
void h_Conveyor::move_vel(int vel)
{
    pros::c::motor_move_velocity(m_motor_t, vel);
    pros::c::motor_move_velocity(m_motor_b, vel);
}

/// Moves the conveyor motors separately.
/// \param vel_t Top velocity in RPM within the range of the previously supplied cartridge.
/// \param vel_b Bottom velocity in RPM within the range of the previously supplied cartridge.
void h_Conveyor::move_vel(int vel_t, int vel_b)
{
    pros::c::motor_move_velocity(m_motor_t, vel_t);
    pros::c::motor_move_velocity(m_motor_b, vel_b);
}


//* Telemetry *//

/// Get the average current draw of all motors on the conveyor.
/// \return Average current draw to the closest milliamp.
int h_Conveyor::get_conveyor_current(void)
{
    return std::round((pros::c::motor_get_current_draw(m_motor_t) +
                       pros::c::motor_get_current_draw(m_motor_b)) / 4.0);
}

/// Get the average voltage of all motors on the conveyor.
/// \return Average voltage to the closest millivolt.
int h_Conveyor::get_conveyor_voltage(void)
{
    return std::round((pros::c::motor_get_voltage(m_motor_t) +
                       pros::c::motor_get_voltage(m_motor_b)) / 4.0);
}

/// Get the average power of all motors on the conveyor.
/// \return Average power in watts.
double h_Conveyor::get_conveyor_power(void)
{
    return ((pros::c::motor_get_power(m_motor_t) +
             pros::c::motor_get_power(m_motor_b)) / 4.0);
}

/// Get the average temperature of all motors on the conveyor.
/// \return Average temperature in Celcius.
double h_Conveyor::get_conveyor_temperature(void)
{
    return ((pros::c::motor_get_temperature(m_motor_t) +
             pros::c::motor_get_temperature(m_motor_b)) / 4.0);
}

/// Get the average efficiency of all motors on the conveyor.
/// \return Average efficiency in percentage.
double h_Conveyor::get_conveyor_efficiency(void)
{
    return ((pros::c::motor_get_efficiency(m_motor_t) +
             pros::c::motor_get_efficiency(m_motor_b)) / 4.0);
}

/// Get the current draws of each motor. 
/// In the order of: TOP, BOTTOM
/// \return Current draws in milliamps in a 2-integer tuple.
std::tuple<int, int> h_Conveyor::get_current_per_motor(void)
{
    return std::make_tuple<int, int>(
        pros::c::motor_get_current_draw(m_motor_t),
        pros::c::motor_get_current_draw(m_motor_b)
    );
}

/// Get the voltages of each motor. 
/// In the order of: TOP, BOTTOM
/// \return Voltages in millivolts in a 2-integer tuple.
std::tuple<int, int> h_Conveyor::get_voltage_per_motor(void)
{
    return std::make_tuple<int, int>(
        pros::c::motor_get_voltage(m_motor_t),
        pros::c::motor_get_voltage(m_motor_b)
    );
}

/// Get the power of each motor. 
/// In the order of: TOP, BOTTOM
/// \return Power in watts in a 2-double tuple.
std::tuple<double, double> h_Conveyor::get_power_per_motor(void)
{
    return std::make_tuple<double, double>(
        pros::c::motor_get_power(m_motor_t),
        pros::c::motor_get_power(m_motor_b)
    );
}

/// Get the temperatures of each motor. 
/// In the order of: TOP, BOTTOM
/// \return Temperatures in Celcius in a 2-double tuple.
std::tuple<double, double> h_Conveyor::get_temperature_per_motor(void)
{
    return std::make_tuple<double, double>(
        pros::c::motor_get_temperature(m_motor_t),
        pros::c::motor_get_temperature(m_motor_b)
    );
}

/// Get the efficiencies of each motor. 
/// In the order of: TOP, BOTTOM
/// \return Efficiencies in percentages in a 2-double tuple.
std::tuple<double, double> h_Conveyor::get_efficiency_per_motor(void)
{
    return std::make_tuple<double, double>(
        pros::c::motor_get_efficiency(m_motor_t),
        pros::c::motor_get_efficiency(m_motor_b)
    );
}

/// Get the stopped status of each motor. 
/// In the order of: TOP, BOTTOM
/// \return A 2-boolean tuple.
std::tuple<bool, bool> h_Conveyor::is_stopped_per_motor(void)
{
    return std::make_tuple<bool, bool>(
        pros::c::motor_is_stopped(m_motor_t) ? true : false,
        pros::c::motor_is_stopped(m_motor_b) ? true : false
    );
}

/// Get the over-temperature status of each motor. 
/// In the order of: TOP, BOTTOM
/// \return A 2-boolean tuple.
std::tuple<bool, bool> h_Conveyor::is_over_temp_per_motor(void)
{
    return std::make_tuple<bool, bool>(
        pros::c::motor_is_over_temp(m_motor_t) ? true : false,
        pros::c::motor_is_over_temp(m_motor_b) ? true : false
    );
}


//* Configuration *//

/// \return Conveyor max motor velocity in RPM.
int h_Conveyor::get_max_motor_velocity(void) {return m_max_motor_velocity;}

/// \return Conveyor max top roller velocity in RPM.
int h_Conveyor::get_max_top_roller_velocity(void) {return m_max_top_roller_velocity;}

/// In the order of: TOP, BOTTOM.
/// \return A 2-brake mode tuple.
std::tuple<pros::motor_brake_mode_e, pros::motor_brake_mode_e> h_Conveyor::get_brake_modes(void)
{
    return std::make_tuple(
        m_brake_mode_t, 
        m_brake_mode_b
    );
}

/// \return Current set encoder units.
pros::motor_encoder_units_e h_Conveyor::get_encoder_units(void) {return m_enc_unit;}

/// Sets the brake mode of all conveyor motors.
/// \param brake_mode Supplied motor brake mode.
/// \return this* pointer for function chaining.
h_Conveyor& h_Conveyor::set_brake_mode(pros::motor_brake_mode_e brake_mode)
{
    pros::c::motor_set_brake_mode(m_motor_t, brake_mode);
    pros::c::motor_set_brake_mode(m_motor_b, brake_mode);
    m_brake_mode_t = brake_mode;
    m_brake_mode_b = brake_mode;
    return *this;
}

/// Sets the individual brake modes of the conveyor motors.
/// \param brake_mode_t Supplied top motor brake mode.
/// \param brake_mode_b Supplied bottom motor brake mode.
/// \return this* pointer for function chaining.
h_Conveyor& h_Conveyor::set_brake_mode(pros::motor_brake_mode_e brake_mode_t, pros::motor_brake_mode_e brake_mode_b)
{
    pros::c::motor_set_brake_mode(m_motor_t, brake_mode_t);
    pros::c::motor_set_brake_mode(m_motor_b, brake_mode_b);
    m_brake_mode_t = brake_mode_t;
    m_brake_mode_b = brake_mode_b;
    return *this; 
}

/// Sets the encoder units of the conveyor.
/// \param enc_unit Supplied motor encoder units.
/// \return this* pointer for function chaining.
h_Conveyor& h_Conveyor::set_encoder_units(pros::motor_encoder_units_e enc_unit)
{
    pros::c::motor_set_encoder_units(m_motor_t, enc_unit);
    pros::c::motor_set_encoder_units(m_motor_b, enc_unit);
    m_brake_mode_t = enc_unit;
    m_brake_mode_b = enc_unit;
    return *this;
}
