//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-29
//* Desc: Conveyor class definitons.


//* Headers
#include "main.h"   // Main header.


//* Definitions

/// class - Conveyor
//? This constructor has default values for all values besides the port numbers. 
//? You do not have to specify it all.
/// \param ports            Ports numbers to assign.
/// \param cartridge        Cartridge of all motors.
/// \param enc_unit         Encoder units of all motors.
/// \param brake_mode_cb    Brake mode of the bottom motor.
/// \param brake_mode_ct    Brake mode of the top motor.
h_Conveyor::h_Conveyor(
        const h_Conveyor_Ports &ports, pros::motor_gearset_e cartridge,
        pros::motor_encoder_units_e enc_unit, pros::motor_brake_mode_e brake_mode_cb,
        pros::motor_brake_mode_e brake_mode_ct
    )
    : m_CB {ports.pt_CB, cartridge, false, enc_unit}, m_CT {ports.pt_CT, cartridge, false, enc_unit}
    {
        m_CB.set_brake_mode(brake_mode_cb);
        m_CT.set_brake_mode(brake_mode_ct);
    }

/// Sets the brake mode of the conveyor subsystem.
/// \param brake_mode The brake mode to set the conveyors as.
h_Conveyor& h_Conveyor::set_brake_mode(pros::motor_brake_mode_e brake_mode)
{
    m_CB.set_brake_mode(brake_mode);
    m_CT.set_brake_mode(brake_mode);
    return *this;
}

/// Sets the individual brake modes of the conveyor subsystem.
/// \param brake_mode_cb The brake mode to set the bottom conveyor as.
/// \param brake_mode_ct The brake mode to set the top conveyor as.
h_Conveyor& h_Conveyor::set_brake_mode(pros::motor_brake_mode_e brake_mode_cb, pros::motor_brake_mode_e brake_mode_ct)
{
    m_CB.set_brake_mode(brake_mode_cb);
    m_CT.set_brake_mode(brake_mode_ct);
    return *this;
}

/// Sets the velocity to both conveyor motors with a supplied velocity value.
/// Supplying no or zeroed parameters stops the motors.
/// \param velocity Velocity supplied.
void h_Conveyor::set_vel(int velocity)
{
    m_CB.move_velocity(velocity);
    m_CT.move_velocity(velocity);
}

/// Sets individual velocites to the top and bottom motors with supplied 
/// velocity values. 
//! Has no default parameters. You must supply velocities.
/// \param t_velocity Top conveyor velocity.
/// \param b_velocity Bottom conveyor velocity.
void h_Conveyor::set_vel(int t_velocity, int b_velocity)
{
    m_CB.move_velocity(b_velocity);
    m_CT.move_velocity(t_velocity);
}
