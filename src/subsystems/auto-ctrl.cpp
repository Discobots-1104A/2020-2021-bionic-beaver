// Discobots 1104A comp code.
// Marco Tan, Neil Sachdeva
// 
// Autonomous algorithms are defined here.

#include "subsystems/auto-ctrl.h"

using kMath::Deg;
using kMath::Inch;
using kAuto::k_Dist_Mode;


//> Public Functions <//

// Construct an Auto_PID object for PID control.
// \param P
//      The proportional gain.
// \param I
//      The integral gain.
// \param D
//      The derivative gain.
// \param i_winThrsh
//      The integral windup threshold.
// \param sample_rate
//      How often to sample measurements in milliseconds.
// \param mode
//      Whether to treat lengths as straight lines or arc lengths.
// \return An Auto_PID object.
Auto_PID::Auto_PID
    (double P, double I, double D, double i_winThrsh, int sample_rate, k_Dist_Mode mode)
    : kP{P}, kI{I}, kD{D}, dist_mode{mode}, k_sample_rate{sample_rate}, kI_winThrsh{i_winThrsh}
    {}

// Set the heading target of the PID controller.
// \param head
//      The heading target.
auto Auto_PID::Set_Target(const Deg &head) -> Auto_PID&
{
    targ_Head = head;
    return *this;
}

// Set the distance target of the PID controller.
// \param dist
//      The distance target.
auto Auto_PID::Set_Target(const Inch &dist) -> Auto_PID&
{
    targ_Dist = dist;
    return *this;
}

// Set the distance mode of the PID controller.
// \param mode
//      The distance mode.
auto Auto_PID::Set_Dist_Mode(const k_Dist_Mode &mode) -> Auto_PID&
{
    dist_mode = mode;
    return *this;
}

// Begin execution of the PID controller towards a target. 
// If supplied with only a distance, the robot will drive in a straight line. 
// If supplied with only a heading, the robot will turn on a point. 
// If supplied with both a distance and heading, the robot will swerve to the target.
auto Auto_PID::Drive() -> void
{
    if (targ_Head.var && targ_Dist.var) // Swerve turn.
    {
        
    }
    else if (targ_Dist.var)             // Straight.
    {

    }
    else if (targ_Head.var)             // Point turn.
    {

    }
}
