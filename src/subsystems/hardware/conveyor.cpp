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
    : m_CB {ports.pt_CB, cartridge, true, enc_unit}, m_CT {ports.pt_CT, cartridge, true, enc_unit}
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

/// "Resets" the positions of the motors' internal encoders of the conveyors. 
//! Does not actually reset the encoders. Instead, it sets its zero 
//! to the current position.
h_Conveyor& h_Conveyor::reset_enc()
{
    m_CT.tare_position();
    m_CB.tare_position();
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

/// Move the conveyors based on an absolute position with supplied position and 
/// velocity values.
//? This is a very niche function for autonomous purposes. 
//! Has no default parameters. You must supply position and velocity. 
/// \param position The position to move to in the units supplied.
/// \param velocity The velocity to move towards the position.
void h_Conveyor::set_abs(double position, int velocity)
{
    m_CT.move_absolute(position, velocity);
    m_CB.move_absolute(position, velocity);
}

/// This is an overload for the set_abs function that allows for control over the 
/// individual rollers. Moves them based on the supplied position and velocity 
/// values. 
//? This is a very niche function for autonomous purposes. 
//! Has no default parameters. You must supply position and velocity. 
/// \param t_position The position to move the top rollers, in the units supplied.
/// \param b_position The position to move the bottom rollers, in the units supplied.
/// \param t_velocity The velocity to move the top rollers towards said position.
/// \param b_velocity The velocity to move the bottom rollers towards said position.
void h_Conveyor::set_abs(double t_position, double b_position, int t_velocity, int b_velocity)
{
    m_CT.move_absolute(t_position, t_velocity);
    m_CB.move_absolute(b_position, b_velocity);
}
