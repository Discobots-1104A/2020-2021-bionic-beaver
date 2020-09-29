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
h_Analog_Sen_Ports::h_Analog_Sen_Ports(std::uint8_t LT, std::uint8_t RT, std::uint8_t MT)
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
        const h_Drive_Ports &ports, pros::motor_gearset_e cartridge, 
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
/// \param brake_mode The brake mode to set the chassis as.
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
/// supplied. Supplying no or zeroed parameters stops the motors.
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
