//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Hardware class declarations.

//! Prefix all objects here with "h_" except for child members and namespaces.

#ifndef HARDWARE_HPP
#define HARDWARE_HPP

//* Headers
#include "api.h"    // PROS API header.


//* Constants
namespace k_Hardware
{
    inline constexpr int mot_pos_range {5};     // Motor positional movement range.
}

//* User-defined types

/// struct - drive Ports.
//? In order of: LF, LB, RF, RB.
struct h_Drive_Ports
{
    std::uint8_t pt_LF;     // Drive port, left front.
    std::uint8_t pt_LB;     // Drive port, left back.
    std::uint8_t pt_RF;     // Drive port, right font.
    std::uint8_t pt_RB;     // Drive port, right back.
};

/// struct - Conveyor ports.
//? In order of: bottom, top.
struct h_Conveyor_Ports
{
    std::uint8_t pt_CB;     // Conveyor port, bottom.
    std::uint8_t pt_CT;     // Conveyor port, top.
};

/// struct - Intake ports.
//? In order of: left, right.
struct h_Intake_Ports
{
    std::uint8_t pt_IL;     // Intake port, left.
    std::uint8_t pt_IR;     // Intake port, right.
};

/// struct - Smart sensor ports.
//? In order of: IMU, Vision
struct h_Smart_Sen_Ports
{
    std::uint8_t pt_IMU;    // Smart sensor port, IMU.
    std::uint8_t pt_Vision; // Smart sensor port, Vision.
};

/// struct - Analog sensor ports. 
//! Use only the top port number. 
//? In order of: Left tracking wheel, right tracking wheel, middle tracking wheel. 
struct h_Analog_Sen_Ports
{
    std::uint8_t pt_Enc_LT; // Analog port, encoder left top.
    std::uint8_t pt_Enc_LB; // Analog port, encoder left bottom.
    std::uint8_t pt_Enc_RT; // Analog port, encoder right top.
    std::uint8_t pt_Enc_RB; // Analog port, encoder right bottom.
    std::uint8_t pt_Enc_MT; // Analog port, encoder middle top.
    std::uint8_t pt_Enc_MB; // Analog port, encoder middle bottom.

    h_Analog_Sen_Ports(std::uint8_t LT, std::uint8_t RT, std::uint8_t MT);
};

/// class - Chassis.
/// Has all necessary objects and functions.
class h_Chassis
{
public:
    h_Chassis(   
            const h_Drive_Ports &ports, 
            pros::motor_gearset_e cartridge = pros::E_MOTOR_GEARSET_18,
            pros::motor_encoder_units_e enc_unit = pros::E_MOTOR_ENCODER_COUNTS,
            pros::motor_brake_mode_e brake_mode = pros::E_MOTOR_BRAKE_COAST
        );
    h_Chassis& set_brake_mode(pros::motor_brake_mode_e brake_mode);
    h_Chassis& reset_enc();
    h_Chassis& drive_rel(double position, int velocity);
    h_Chassis& drive_abs(double position, int velocity);
    void drive_vel(int l_velocity = 0, int r_velocity = 0);
    void drive_vol(int l_voltage = 0, int r_voltage = 0);
    void wait_until_settled();

private:
    bool is_settled = true;
    pros::Motor m_LF;
    pros::Motor m_LB;
    pros::Motor m_RF;
    pros::Motor m_RB;

    double avg_motor_pos();

};

/// class - Conveyor.
/// Has all the necessary objects and functions.
class h_Conveyor
{
public:
    h_Conveyor(
        const h_Conveyor_Ports &ports,
        pros::motor_gearset_e cartridge = pros::E_MOTOR_GEARSET_06,
        pros::motor_encoder_units_e enc_unit = pros::E_MOTOR_ENCODER_COUNTS,
        pros::motor_brake_mode_e brake_mode_cb = pros::E_MOTOR_BRAKE_BRAKE,
        pros::motor_brake_mode_e brake_mode_ct = pros::E_MOTOR_BRAKE_HOLD
    );
    h_Conveyor& set_brake_mode(pros::motor_brake_mode_e brake_mode);
    h_Conveyor& set_brake_mode(pros::motor_brake_mode_e brake_mode_cb, pros::motor_brake_mode_e brake_mode_ct);
    void set_vel(int velocity = 0);
    void set_vel(int t_velocity, int b_velocity);

private:
    pros::Motor m_CB;
    pros::Motor m_CT;

};

/// class - Intake
/// Has all the necessary objects and functions.
class h_Intake
{
public:
    h_Intake(
        const h_Intake_Ports &ports,
        pros::motor_gearset_e cartridge = pros::E_MOTOR_GEARSET_06,
        pros::motor_encoder_units_e enc_unit = pros::E_MOTOR_ENCODER_COUNTS,
        pros::motor_brake_mode_e brake_mode = pros::E_MOTOR_BRAKE_HOLD
    );
    h_Intake& set_brake_mode(pros::motor_brake_mode_e brake_mode);
    h_Intake& set_brake_mode(pros::motor_brake_mode_e brake_mode_l, pros::motor_brake_mode_e brake_mode_r);
    void set_vel(int velocity = 0);
    void set_vel(int l_velocity, int r_velocity);

private:
    pros::Motor m_IL;
    pros::Motor m_IR;

};

#endif  // HARDWARE_HPP
