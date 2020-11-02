//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Chassis class declarations

#ifndef CHASSIS_HPP
#define CHASSIS_HPP

#include "api.h"


/// Chassis scales
struct h_Chassis_Scales
{
    // Chassis length & width
    struct h_Chassis_Length_Width
    {
        double  m_length;   // Length in inches
        double  m_width;    // Width in inches
    } frame_dims;

    // Chassis wheel dimensions
    struct h_Chassis_Wheel_Dims
    {
        double  m_wheel_diameter;   // Diameter in inches
        double  m_wheelbase_length; // Wheelbase length in inches
    } wheel_dims;

    // Chassis configs
    struct h_Chassis_Misc
    {
        int m_max_motor_velocity;   // Max motor velocity in RPM
        int m_max_total_velocity;   // Max total velocity in RPM
        double  m_gear_ratio;   // Overall gear ratio in decimal form
    } misc;
};

/// Chassis motor port numbers
struct h_Chassis_Port_Numbers
{
    int     m_motor_lf;     // Motor left front
    int     m_motor_lb;     // Motor left back
    int     m_motor_rf;     // Motor right front
    int     m_motor_rb;     // Motor right back
};

/// Chassis class. Contains all variables and member functions pertaining to 
/// the operation of the chassis, as well as some constants used for some math 
/// later. "Skid_Steer" because we anticipate the use of an XDrive later, so we 
/// might make another class for it.
class h_Skid_Steer_Chassis
{
public:
    // Constructors and destructors

    h_Skid_Steer_Chassis(
        h_Chassis_Port_Numbers      port_nums,
        h_Chassis_Scales            scales,
        pros::motor_gearset_e       cart        = pros::E_MOTOR_GEARSET_18,
        pros::motor_brake_mode_e    brake_mode  = pros::E_MOTOR_BRAKE_COAST,
        pros::motor_encoder_units_e enc_unit    = pros::E_MOTOR_ENCODER_COUNTS
    );
    ~h_Skid_Steer_Chassis();


    // Movement

    void move(int vol);
    void move(int vol_l, int vol_r);
    void move_vel(int vel);
    void move_vel(int vel_l, int vel_r);


    // Telemetry - chassis average

    int     get_chassis_efficiency(void);
    int     get_chassis_current(void);
    double  get_chassis_power(void);
    double  get_chassis_temperature(void);
    double  get_chassis_voltage(void);


    // Telemetry - per motor

    std::tuple<int, int, int, int>              get_efficiency_per_motor(void);
    std::tuple<int, int, int, int>              get_current_per_motor(void);
    std::tuple<double, double, double, double>  get_power_per_motor(void);
    std::tuple<double, double, double, double>  get_temperature_per_motor(void);
    std::tuple<double, double, double, double>  get_voltage_per_motor(void);
    std::tuple<bool, bool, bool, bool>          is_stopped_per_motor(void);
    std::tuple<bool, bool, bool, bool>          is_over_temp_per_motor(void);


    // Configuration

    double  get_length(void);
    double  get_width(void);
    double  get_wheel_diameter(void);
    double  get_wheelbase_lenth(void);
    double  get_gear_ratio(void);
    int     get_max_motor_velocity(void);
    int     get_max_total_velocity(void);    
    pros::motor_brake_mode_e        get_brake_mode(void);
    pros::motor_encoder_units_e     get_encoder_units(void);
    h_Skid_Steer_Chassis& set_brake_mode(pros::motor_brake_mode_e brake_mode);
    h_Skid_Steer_Chassis& set_encoder_units(pros::motor_encoder_units_e enc_unit);

private:
    // Port numbers
    const std::uint8_t  m_motor_lf;     // Motor left front
    const std::uint8_t  m_motor_lb;     // Motor left back
    const std::uint8_t  m_motor_rf;     // Motor right front
    const std::uint8_t  m_motor_rb;     // Motor right back


    // Motor config
    const pros::motor_gearset_e m_cart;         // Gearset of chassis
                                                //! Const b/c it should never change after init
    pros::motor_brake_mode_e    m_brake_mode;   // Brake mode of chassis
    pros::motor_encoder_units_e m_enc_unit;     // Encoder units of chassis


    // Chassis scales
    //! Const b/c they should never change after init
    const double    m_length;               // Robot length in inches
    const double    m_width;                // Robot width in inches
    const double    m_wheel_diameter;       // Diameter in inches
    const double    m_wheelbase_length;     // Wheelbase length in inches
    const double    m_gear_ratio;           // Overall gear ratio in decimal form
    const int       m_max_motor_velocity;   // Max motor velocity in RPM
    const int       m_max_total_velocity;   // Max total velocity in RPM

};

#endif  // CHASSIS_HPP
