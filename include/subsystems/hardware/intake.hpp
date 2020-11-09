//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Intake class declarations

#ifndef INTAKE_HPP
#define INTAKE_HPP

#include "api.h"


/// Intake scales
struct h_Intake_Scales
{
    int m_max_motor_velocity;   // Max motor velocity in RPM  
};

/// Intake motor port numbers
struct h_Intake_Port_Numbers
{
    int     m_motor_l;  // Motor left
    int     m_motor_r;  // Motor right
};

/// Intake class. Contains all variables and member functions pertaining to 
/// the operation of the intake.
class h_Intake
{
public:
    // Constructor and destructor

    h_Intake(
        const h_Intake_Port_Numbers&    port_nums,
        const h_Intake_Scales&          scales,
        pros::motor_gearset_e           cart            = pros::E_MOTOR_GEARSET_06,
        pros::motor_brake_mode_e        brake_mode      = pros::E_MOTOR_BRAKE_HOLD,
        pros::motor_encoder_units_e     enc_unit        = pros::E_MOTOR_ENCODER_COUNTS
    );
    ~h_Intake();


    // Movement

    void move_vel(int vel);
    void move_vel(int vel_t, int vel_b);


    // Telemetry - conveyor average

    int     get_intake_current(void);
    int     get_intake_voltage(void);
    double  get_intake_power(void);
    double  get_intake_temperature(void);
    double  get_intake_efficiency(void);


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
    pros::motor_brake_mode_e        get_brake_mode(void);
    pros::motor_encoder_units_e     get_encoder_units(void);
    h_Intake& set_brake_mode(pros::motor_brake_mode_e brake_mode);
    h_Intake& set_encoder_units(pros::motor_encoder_units_e enc_unit);

private:
    // Port numbers
    const std::uint8_t  m_motor_l;      // Motor left
    const std::uint8_t  m_motor_r;      // Motor right


    // Motor config
    const pros::motor_gearset_e m_cart;         // Gearset of intake
                                                //! Const b/c it should never change after init
    pros::motor_brake_mode_e    m_brake_mode;   // Brake mode of intake
    pros::motor_encoder_units_e m_enc_unit;     // Encoder units of intake


    // Intake scales
    //! Const b/c they should never change after init
    const int   m_max_motor_velocity;       // Max motor velocity in RPM  

};

#endif