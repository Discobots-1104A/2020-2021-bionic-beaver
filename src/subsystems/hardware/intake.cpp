//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-29
//* Desc: Intake class definitons.


//* Headers
#include "main.h"   // Main header.


//* Definitions

/// class - Intake 
//? This constructor has default values for all values besides the port numbers. 
//? You do not have to specify it all.
/// \param ports        Ports numbers to assign.
/// \param cartridge    Cartridge of all motors.
/// \param enc_unit     Encoder units of all motors.
/// \param brake_mode   Brake mode of all motors.
h_Intake::h_Intake (
        const h_Intake_Ports &ports, pros::motor_gearset_e cartridge,
        pros::motor_encoder_units_e enc_unit, pros::motor_brake_mode_e brake_mode
    )
    : m_IL {ports.pt_IL, cartridge, false, enc_unit}, m_IR {ports.pt_IR, cartridge, true, enc_unit}
    {
        m_IL.set_brake_mode(brake_mode);
        m_IR.set_brake_mode(brake_mode);
    }

/// Sets the brake mode of the intake subsystem.
/// \param brake_mode The brake mode to set the intakes as.
h_Intake& h_Intake::set_brake_mode(pros::motor_brake_mode_e brake_mode)
{
    m_IL.set_brake_mode(brake_mode);
    m_IR.set_brake_mode(brake_mode);
    return *this;
}

/// Sets the individual brake modes of the intake subsystem. 
//? You will most likely never need to use this.
/// \param brake_mode_l The brake mode to set the left intake as.
/// \param brake_mode_r The brake mode to set the right intake as.
h_Intake& h_Intake::set_brake_mode(pros::motor_brake_mode_e brake_mode_l, pros::motor_brake_mode_e brake_mode_r)
{
    m_IL.set_brake_mode(brake_mode_l);
    m_IR.set_brake_mode(brake_mode_r);
    return *this;
}

/// "Resets" the positions of the motors' internal encoders of the intakes. 
//! Does not actually reset the encoders. Instead, it sets its zero 
//! to the current position.
h_Intake& h_Intake::reset_enc()
{
    m_IL.tare_position();
    m_IR.tare_position();
    return *this;
}

/// Sets the velocity to both intake motors with a supplied velocity value. 
/// Supplying no or zeroed parameters stops the motors.
/// \param velocity Velocity supplied.
void h_Intake::set_vel(int velocity)
{
    m_IL.move_velocity(velocity);
    m_IR.move_velocity(velocity);
}

/// Sets individual velocites to the left and right motors with supplied 
/// velocity values. 
//? You will most likely never need to use this. 
//! Has no default parameters. You must supply velocities.
/// \param l_velocity Left intake velocity.
/// \param r_velocity Right intake velocity.
void h_Intake::set_vel(int l_velocity, int r_velocity)
{
    m_IL.move_velocity(l_velocity);
    m_IR.move_velocity(r_velocity);
}

/// Move the intakes based on an absolute position with supplied position and 
/// velocity values.
//? This is a very niche function for like a single drive control function. 
//! Has no default parameters. You must supply position and velocity. 
/// \param position The position to move to in the units supplied.
/// \param velocity The velocity to move towards the position.
void h_Intake::set_abs(double position, int velocity)
{
    m_IL.move_absolute(position, velocity);
    m_IR.move_absolute(position, velocity);
}
