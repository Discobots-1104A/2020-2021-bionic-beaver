//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Hardware class definitions.


//* Headers
#include "main.h"   // Main header.


//* Helper Functions

/// Gets the absolute average of the motor encoder positions.
double h_Chassis::avg_motor_pos()
{
    return (std::abs(
        (m_LF.get_position() + m_LB.get_position() + 
         m_RF.get_position() + m_RB.get_position()) / 4
    ));
}

//* Definitions

/// struct - Analog sensor ports.
/// \param LT Top port of the left OSR.
/// \param RT Top port of the right OSR.
/// \param MT Top port of the middle OSR.
h_Analog_Sen_Ports::h_Analog_Sen_Ports(int LT, int RT, int MT)
    : pt_Enc_LT {LT}, pt_Enc_LB {++LT}, pt_Enc_RT {RT}, pt_Enc_RB {++RT} , pt_Enc_MT {MT} , pt_Enc_MB {++MT}
    {}

/// class - Chassis. 
//? This constructor has default values for all values besides the port numbers. 
//? You do not have to specify it all.
/// \param ports        Ports numbers to assign.
/// \param cartridge    Cartridge of all motors.
/// \param enc_unit     Encoder units of all motors.
/// \param brake_mode   Brake mode of all motors.
h_Chassis::h_Chassis(
        h_Drive_Ports ports, pros::motor_gearset_e cartridge, 
        pros::motor_encoder_units_e enc_unit, pros::motor_brake_mode_e brake_mode
    )
    : m_LF {ports.pt_LF, cartridge, false, enc_unit}, m_LB {ports.pt_LB, cartridge, false, enc_unit},
      m_RF {ports.pt_RF, cartridge, true, enc_unit},  m_RB {ports.pt_RB, cartridge, true, enc_unit}
    {
        m_LF.set_brake_mode(brake_mode);
        m_LB.set_brake_mode(brake_mode);
        m_RF.set_brake_mode(brake_mode);
        m_RB.set_brake_mode(brake_mode);
    }

/// Sets the brake mode of the chassis.
/// \param brake_mode The brake mode to set the chassis.
h_Chassis& h_Chassis::set_brake_mode(pros::motor_brake_mode_e brake_mode)
{
    m_LF.set_brake_mode(brake_mode);
    m_LB.set_brake_mode(brake_mode);
    m_RF.set_brake_mode(brake_mode);
    m_RB.set_brake_mode(brake_mode);
    return *this;
}

/// "Resets" the positions of the motors' internal encoders on the chassis. 
//! Does not actually reset the encoders. Instead, it sets its zero 
//! to the current position.
h_Chassis& h_Chassis::reset_enc()
{
    m_LF.tare_position();
    m_LB.tare_position();
    m_RF.tare_position();
    m_RB.tare_position();
    return *this;
}

/// Drives the chassis in a line to a position relative to the current position.
/// \param position The position to move to in the units supplied.
/// \param velocity The velocity to move towards the position.
h_Chassis& h_Chassis::drive_rel(double position, int velocity)
{
    m_LF.move_relative(position, velocity);
    m_LB.move_relative(position, velocity);
    m_RF.move_relative(position, velocity);
    m_RB.move_relative(position, velocity);
    is_settled = false;
    return *this;
}

/// Drives the chassis in a line to a position relative to the zero set on the motors.
/// \param position The position to move to in the units supplied.
/// \param velocity The velocity to move towards the position.
h_Chassis& h_Chassis::drive_abs(double position, int velocity)
{
    m_LF.move_absolute(position, velocity);
    m_LB.move_absolute(position, velocity);
    m_RF.move_absolute(position, velocity);
    m_RB.move_absolute(position, velocity);
    is_settled = false;
    return *this;
}

/// Drives the chassis based on velocity. Max velocity based on chassis cartridge 
/// supplied. Supplying no parameters stops the motors.
/// \param l_velocity Left side velocity.
/// \param r_velocity Right side velocity.
void h_Chassis::drive_vel(int l_velocity, int r_velocity)
{
    m_LF.move_velocity(l_velocity);
    m_LB.move_velocity(l_velocity);
    m_RF.move_velocity(r_velocity);
    m_RB.move_velocity(r_velocity);
}

/// Drives the chassis based on voltage values returned from the joysticks.
/// Supplying no or zeroed paramters stops the motors.
/// \param l_voltage Left side voltage.
/// \param r_voltage Right side voltage.
void h_Chassis::drive_vol(int l_voltage, int r_voltage)
{
    m_LF.move(l_voltage);
    m_LB.move(l_voltage);
    m_RF.move(r_voltage);
    m_RB.move(r_voltage);
}

/// Halts all further execution until the chassis has reached its target.
void h_Chassis::wait_until_settled()
{
    if (!is_settled)
    {
        while ((m_LF.get_target_position() - avg_motor_pos()) > k_Hardware::mot_pos_range)
            { pros::delay(5); }
    }

    is_settled = true;
}
