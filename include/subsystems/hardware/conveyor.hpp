//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Conveyor class declarations

//TODO: Check if we need to add any necessary constants to the conveyor class.

#ifndef CONVEYOR_HPP
#define CONVEYOR_HPP

#include "api.h"


/// Conveyor scales
struct h_Conveyor_Scales
{
    int m_max_motor_velocity;       // Max motor velocity in RPM
    int m_max_top_roller_velocity;  // Max top roller velocity in RPM
};

/// Conveyor motor port numbers
struct h_Conveyor_Port_Numbers
{
    int     m_motor_t;  // Motor top
    int     m_motor_b;  // Motor bottom
};

/// Conveyor class. Contains all variables and member functions pertaining to 
/// the operation of the conveyor.
class h_Conveyor
{
public:
    // Constructor and destructor

    h_Conveyor(
        h_Conveyor_Port_Numbers     port_nums,
        h_Conveyor_Scales           scales,
        pros::motor_gearset_e       cart            = pros::E_MOTOR_GEARSET_06,
        pros::motor_brake_mode_e    brake_mode_t    = pros::E_MOTOR_BRAKE_HOLD,
        pros::motor_brake_mode_e    brake_mode_b    = pros::E_MOTOR_BRAKE_HOLD,
        pros::motor_encoder_units_e enc_unit        = pros::E_MOTOR_ENCODER_COUNTS
    );
    ~h_Conveyor();


    // Movement

    void move_vel(int vel);
    void move_vel(int vel_t, int vel_b);


    // Telemetry - conveyor average

    int     get_conveyor_current(void);
    int     get_conveyor_voltage(void);
    double  get_conveyor_power(void);
    double  get_conveyor_temperature(void);
    double  get_conveyor_efficiency(void);


    // Telemetry - per motor

    std::tuple<int, int>            get_current_per_motor(void);
    std::tuple<int, int>            get_voltage_per_motor(void);
    std::tuple<double, double>      get_power_per_motor(void);
    std::tuple<double, double>      get_temperature_per_motor(void);
    std::tuple<double, double>      get_efficiency_per_motor(void);
    std::tuple<bool, bool>          is_stopped_per_motor(void);
    std::tuple<bool, bool>          is_over_temp_per_motor(void);


    // Configuration

    int get_max_motor_velocity(void);
    int get_max_top_roller_velocity(void);
    std::tuple<pros::motor_brake_mode_e, pros::motor_brake_mode_e>  get_brake_modes(void);
    pros::motor_encoder_units_e get_encoder_units(void);
    h_Conveyor& set_brake_mode(pros::motor_brake_mode_e brake_mode);
    h_Conveyor& set_brake_mode(pros::motor_brake_mode_e brake_mode_t, pros::motor_brake_mode_e brake_mode_b);
    h_Conveyor& set_encoder_units(pros::motor_encoder_units_e enc_unit);

private:
    // Port numbers
    const std::uint8_t  m_motor_t;      // Motor top
    const std::uint8_t  m_motor_b;      // Motor bottom


    // Motor config
    const pros::motor_gearset_e m_cart;         // Gearset of conveyor
                                                //! Const b/c it should never change after init
    pros::motor_brake_mode_e    m_brake_mode_t; // Brake mode of top motor
    pros::motor_brake_mode_e    m_brake_mode_b; // Brake mode of bottom motor
    pros::motor_encoder_units_e m_enc_unit;     // Encoder units of conveyor


    // Conveyor scales
    //! Const b/c they should never change after init
    const int   m_max_motor_velocity;       // Max motor velocity in RPM
    const int   m_max_top_roller_velocity;  // Max top roller velocity in RPM  

};

#endif  // CONVEYOR_HPP
