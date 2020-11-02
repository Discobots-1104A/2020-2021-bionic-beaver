//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Chassis class definitions

#include "main.h"


//* Constructor and destructor *//

/// Skid steer chassis constructor. Port nums and scales must be supplied. Motor 
/// configs have default parameters. Interfaces with PROS C functions to configure 
/// each drive motor.
/// \param port_nums Supplied port numbers. Negative numbers reverse the motor.
/// \param scales Supplied chassis scales.
/// \param cart Supplied motor cartridges.
/// \param brake_mode Supplied motor brake mode.
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

    // Assign motor cartridges
    pros::c::motor_set_gearing(m_motor_lf, m_cart);
    pros::c::motor_set_gearing(m_motor_lb, m_cart);
    pros::c::motor_set_gearing(m_motor_rf, m_cart);
    pros::c::motor_set_gearing(m_motor_rb, m_cart);

    // Assign brake modes
    set_brake_mode(brake_mode);

    // Assign encoder units
    set_encoder_units(enc_unit);
}


//* Movement *//

/// Moves the left and right side motors together to drive straight.
/// \param vol Joystick voltage from -127 - 127.
void h_Skid_Steer_Chassis::move(int vol)
{
    pros::c::motor_move(m_motor_lf, vol);
    pros::c::motor_move(m_motor_lb, vol);
    pros::c::motor_move(m_motor_rf, vol);
    pros::c::motor_move(m_motor_rb, vol);
}

/// Moves left and right side motors independently from each other.
/// \param vol_l Left side joystick voltage from -127 - 127.
/// \param vol_r Right side joystick voltage from -127 - 127.
void h_Skid_Steer_Chassis::move(int vol_l, int vol_r)
{
    pros::c::motor_move(m_motor_lf, vol_l);
    pros::c::motor_move(m_motor_lb, vol_l);
    pros::c::motor_move(m_motor_rf, vol_r);
    pros::c::motor_move(m_motor_rb, vol_r);
}

/// Move the left and right side motors together to drive straight.
/// \param vel Velocity in RPM within the range of the previously supplied cartridge.
void h_Skid_Steer_Chassis::move_vel(int vel)
{
    pros::c::motor_move_velocity(m_motor_lf, vel);
    pros::c::motor_move_velocity(m_motor_lb, vel);
    pros::c::motor_move_velocity(m_motor_rf, vel);
    pros::c::motor_move_velocity(m_motor_rb, vel);
}

/// Move left and right side motors independently from each other.
/// \param vel_l Left side velocity in RPM within the range of the previously supplied cartridge.
/// \param vel_r Right side velocity in RPM within the range of the previously supplied cartridge.
void h_Skid_Steer_Chassis::move_vel(int vel_l, int vel_r)
{
    pros::c::motor_move_velocity(m_motor_lf, vel_l);
    pros::c::motor_move_velocity(m_motor_lb, vel_l);
    pros::c::motor_move_velocity(m_motor_rf, vel_r);
    pros::c::motor_move_velocity(m_motor_rb, vel_r);
}


//* Telemetry *//

/// Get the average current draw of all motors on the chassis.
/// \return Average current draw to the closest milliamp.
int h_Skid_Steer_Chassis::get_chassis_current(void)
{
    return std::round((pros::c::motor_get_current_draw(m_motor_lf) +
                       pros::c::motor_get_current_draw(m_motor_lb) +
                       pros::c::motor_get_current_draw(m_motor_rf) +
                       pros::c::motor_get_current_draw(m_motor_rb)) / 4.0);
}

/// Get the average voltage of all motors on the chassis.
/// \return Average voltage to the closest millivolt.
int h_Skid_Steer_Chassis::get_chassis_voltage(void)
{
    return std::round((pros::c::motor_get_voltage(m_motor_lf) +
                       pros::c::motor_get_voltage(m_motor_lb) +
                       pros::c::motor_get_voltage(m_motor_rf) +
                       pros::c::motor_get_voltage(m_motor_rb)) / 4.0);
}

/// Get the average power of all motors on the chassis.
/// \return Average power in watts.
double h_Skid_Steer_Chassis::get_chassis_power(void)
{
    return ((pros::c::motor_get_power(m_motor_lf) +
             pros::c::motor_get_power(m_motor_lb) +
             pros::c::motor_get_power(m_motor_rf) +
             pros::c::motor_get_power(m_motor_rb)) / 4.0);
}

/// Get the average temperature of all motors on the chassis.
/// \return Average temperature in Celcius.
double h_Skid_Steer_Chassis::get_chassis_temperature(void)
{
    return ((pros::c::motor_get_temperature(m_motor_lf) +
             pros::c::motor_get_temperature(m_motor_lb) +
             pros::c::motor_get_temperature(m_motor_rf) +
             pros::c::motor_get_temperature(m_motor_rb)) / 4.0);
}

/// Get the average efficiency of all motors on the chassis.
/// \return Average efficiency in percentage.
double h_Skid_Steer_Chassis::get_chassis_efficiency(void)
{
    return ((pros::c::motor_get_efficiency(m_motor_lf) +
             pros::c::motor_get_efficiency(m_motor_lb) +
             pros::c::motor_get_efficiency(m_motor_rf) +
             pros::c::motor_get_efficiency(m_motor_rb)) / 4.0);
}

/// Get the current draws of each motor. 
/// In the order of: LF, LB, RF, RB.
/// \return Current draws in milliamps in a 4-integer tuple.
std::tuple<int, int, int, int> h_Skid_Steer_Chassis::get_current_per_motor(void)
{
    return std::make_tuple<int, int, int, int>(
        pros::c::motor_get_current_draw(m_motor_lf),
        pros::c::motor_get_current_draw(m_motor_lb),
        pros::c::motor_get_current_draw(m_motor_rf),
        pros::c::motor_get_current_draw(m_motor_rb)
    );
}

/// Get the voltages of each motor. 
/// In the order of: LF, LB, RF, RB.
/// \return Voltages in millivolts in a 4-integer tuple.
std::tuple<int, int, int, int> h_Skid_Steer_Chassis::get_voltage_per_motor(void)
{
    return std::make_tuple<int, int, int, int>(
        pros::c::motor_get_voltage(m_motor_lf),
        pros::c::motor_get_voltage(m_motor_lb),
        pros::c::motor_get_voltage(m_motor_rf),
        pros::c::motor_get_voltage(m_motor_rb)
    );
}

/// Get the power of each motor. 
/// In the order of: LF, LB, RF, RB.
/// \return Power in watts in a 4-double tuple.
std::tuple<double, double, double, double> h_Skid_Steer_Chassis::get_power_per_motor(void)
{
    return std::make_tuple<double, double, double, double>(
        pros::c::motor_get_power(m_motor_lf),
        pros::c::motor_get_power(m_motor_lb),
        pros::c::motor_get_power(m_motor_rf),
        pros::c::motor_get_power(m_motor_rb)
    );
}

/// Get the temperatures of each motor. 
/// In the order of: LF, LB, RF, RB.
/// \return Temperatures in Celcius in a 4-double tuple.
std::tuple<double, double, double, double> h_Skid_Steer_Chassis::get_temperature_per_motor(void)
{
    return std::make_tuple<double, double, double, double>(
        pros::c::motor_get_temperature(m_motor_lf),
        pros::c::motor_get_temperature(m_motor_lb),
        pros::c::motor_get_temperature(m_motor_rf),
        pros::c::motor_get_temperature(m_motor_rb)
    );
};

/// Get the efficiencies of each motor. 
/// In the order of: LF, LB, RF, RB.
/// \return Efficiencies in percentages in a 4-double tuple.
std::tuple<double, double, double, double> h_Skid_Steer_Chassis::get_efficiency_per_motor(void)
{
    return std::make_tuple<double, double, double, double>(
        pros::c::motor_get_efficiency(m_motor_lf),
        pros::c::motor_get_efficiency(m_motor_lb),
        pros::c::motor_get_efficiency(m_motor_rf),
        pros::c::motor_get_efficiency(m_motor_rb)
    );
}

/// Get the stopped status of each motor. 
/// In the order of: LF, LB, RF, RB.
/// \return A 4-boolean tuple.
std::tuple<bool, bool, bool, bool> h_Skid_Steer_Chassis::is_stopped_per_motor(void)
{
    return std::make_tuple<bool, bool, bool, bool>(
        pros::c::motor_is_stopped(m_motor_lf) ? true : false,
        pros::c::motor_is_stopped(m_motor_lb) ? true : false,
        pros::c::motor_is_stopped(m_motor_rf) ? true : false,
        pros::c::motor_is_stopped(m_motor_rb) ? true : false
    );
}

/// Get the over-temperature status of each motor. 
/// In the order of: LF, LB, RF, RB.
/// \return A 4-boolean tuple.
std::tuple<bool, bool, bool, bool> h_Skid_Steer_Chassis::is_over_temp_per_motor(void)
{
    return std::make_tuple<bool, bool, bool, bool>(
        pros::c::motor_is_over_temp(m_motor_lf) ? true : false,
        pros::c::motor_is_over_temp(m_motor_lb) ? true : false,
        pros::c::motor_is_over_temp(m_motor_rf) ? true : false,
        pros::c::motor_is_over_temp(m_motor_rb) ? true : false
    );
}


//* Configuration *//

/// \return Robot length in inches.
double h_Skid_Steer_Chassis::get_length(void) {return m_length;}

/// \return Robot width in inches.
double h_Skid_Steer_Chassis::get_width(void) {return m_width;}

/// \return Robot wheel diameter in inches.
double h_Skid_Steer_Chassis::get_wheel_diameter(void) {return m_wheel_diameter;}

/// \return Robot wheelbase length in inches.
double h_Skid_Steer_Chassis::get_wheelbase_lenth(void) {return m_wheelbase_length;}

/// \return Robot chassis gear ratio in decimal form.
double h_Skid_Steer_Chassis::get_gear_ratio(void) {return m_gear_ratio;}

/// \return Robot max motor velocity in RPM.
int h_Skid_Steer_Chassis::get_max_motor_velocity(void) {return m_max_motor_velocity;}

/// \return Robot max total velocity in RPM.
int h_Skid_Steer_Chassis::get_max_total_velocity(void) {return m_max_total_velocity;}

/// \return Current set brake mode.
pros::motor_brake_mode_e h_Skid_Steer_Chassis::get_brake_mode(void) {return m_brake_mode;}

/// \return Current set encoder units.
pros::motor_encoder_units_e h_Skid_Steer_Chassis::get_encoder_units(void) {return m_enc_unit;}

/// Sets the brake mode of the chassis.
/// \param brake_mode Supplied motor brake mode.
/// \return this* pointer for function chaining.
h_Skid_Steer_Chassis& h_Skid_Steer_Chassis::set_brake_mode(pros::motor_brake_mode_e brake_mode)
{
    pros::c::motor_set_brake_mode(m_motor_lf, brake_mode);
    pros::c::motor_set_brake_mode(m_motor_lb, brake_mode);
    pros::c::motor_set_brake_mode(m_motor_rf, brake_mode);
    pros::c::motor_set_brake_mode(m_motor_rb, brake_mode);
    m_brake_mode = brake_mode;
    return *this;
}


/// Sets the encoder units of the chassis.
/// \param enc_unit Supplied motor encoder units.
/// \return this* pointer for function chaining.
h_Skid_Steer_Chassis& h_Skid_Steer_Chassis::set_encoder_units(pros::motor_encoder_units_e enc_unit)
{
    pros::c::motor_set_encoder_units(m_motor_lf, enc_unit);
    pros::c::motor_set_encoder_units(m_motor_lb, enc_unit);
    pros::c::motor_set_encoder_units(m_motor_rf, enc_unit);
    pros::c::motor_set_encoder_units(m_motor_rb, enc_unit);
    m_enc_unit = enc_unit;
    return *this;
}
