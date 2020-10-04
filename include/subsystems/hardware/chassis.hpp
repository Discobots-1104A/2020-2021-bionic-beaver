//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-29
//* Desc: Chassis class declarations.

//! Prefix all objects here with "h_" except for child members and namespaces.

#ifndef H_CHASSIS_HPP
#define H_CHASSIS_HPP

//* Headers
#include "api.h"

//* User-defined types

/// struct - Drive ports.
//? In order of: LF, LB, RF, RB.
struct h_Drive_Ports
{
    std::uint8_t pt_LF;     // Drive port, left front.
    std::uint8_t pt_LB;     // Drive port, left back.
    std::uint8_t pt_RF;     // Drive port, right font.
    std::uint8_t pt_RB;     // Drive port, right back.
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
    void drive_vel(int velocity = 0);
    void drive_vel(int l_velocity, int r_velocity);
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

#endif  // H_CHASSIS_HPP
