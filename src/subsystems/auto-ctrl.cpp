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
    (double P, double I, double D, double i_winThrsh, int sample_rate, int uncertainty, k_Dist_Mode mode)
    : kP{P}, kI{I}, kD{D}, dist_mode{mode}, k_sample_rate{sample_rate}, k_uncertainty{uncertainty}, kI_winThrsh{i_winThrsh}
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

// Set gains kP, kI, and kD, and optionally, set the integral windup threshold.
// \param P
//      The proportional gain.
// \param I
//      The integral gain.
// \param D
//      The derivative gain.
// \param i_winThrsh
//      The integral windup threshold.
auto Auto_PID::Set_PID(double P, double I, double D, double i_winThrsh) -> Auto_PID&
{
    kP = P; kI = I; kD = D; kI_winThrsh = i_winThrsh;
    return *this;
}

// Begin execution of the PID controller towards a target. 
// If supplied with only a distance, the robot will drive in a straight line. 
// If supplied with only a heading, the robot will turn on a point. 
// If supplied with both a distance and heading, the robot will swerve to the target.
auto Auto_PID::Drive() -> void
{
    Clear_No_Targets();

    if (targ_Head.var && targ_Dist.var) // Swerve turn.
    {
        // Subtract half the robot's length from the distance target depending on the distance mode.
        targ_Dist.var = (dist_mode == kAuto::k_Dist_Mode::STRAIGHT) ? targ_Dist.var : targ_Dist.var - (kRobot::k_Robot_Len / 2);

        // Create two new uninstantiated integer variables for later.
        int targ_Dist_L, targ_Dist_R;\
        
        // If the heading is negative (counterclockwise)
        if (std::signbit(targ_Head.var))
        {
            // Find the main radius.
            // Create two more radii, one longer and one shorter by half the tracking wheel wheelbase length.
            double main_radius {targ_Dist.var / std::abs(kMath::Deg_To_Rad(targ_Head)) },
                   left_radius {main_radius - (kRobot::k_twBase_Len / 2) },
                   right_radius {main_radius + (kRobot::k_twBase_Len / 2)};

            // Create two new distance targets with the arc length formula, using the new radii and the heading.
            // Degrees are in radii. Inches are converted to ticks.
            targ_Dist_L = kMath::Inch_To_Ticks(Inch{left_radius * std::abs(kMath::Deg_To_Rad(targ_Head))});
            targ_Dist_L = kMath::Inch_To_Ticks(Inch{right_radius * std::abs(kMath::Deg_To_Rad(targ_Head))});

            // Keep looping as long as the robot has not reached the uncertainty threshold.
            while ( std::abs(kMath::Inch_To_Ticks(targ_Dist)) - 
                (std::abs((aEncL.get_value() + aEncR.get_value()) / 2) ) > k_uncertainty)
            {
                // Find the current error.
                err_currL = targ_Dist_L - aEncL.get_value();
                err_currR = targ_Dist_R - aEncR.get_value();

                // Find the integral, uses a ternary operator for integral windup prevention.
                int_L = (std::abs(err_currL) <= 0 || std::abs(err_currL) > kI_winThrsh) ? 0 : int_L + err_currL;
                int_R = (std::abs(err_currR) <= 0 || std::abs(err_currR) > kI_winThrsh) ? 0 : int_R + err_currR;

                // Find the derivative.
                derv_L = err_currL - err_prevL;
                derv_R = err_currR - err_prevR;

                // Assign previous error from current error.
                err_prevL = err_currL;
                err_prevR = err_currL;

                // Calculate power. Left side should decrease in power, right side should increase in power.
                int pow_L = 100 - ((err_currL * kP) + (int_L * kI) + (derv_L * kD)),
                    pow_R = 100 + ((err_currR * kP) + (int_R * kI) + (derv_R * kD));

                // Assign powers to max velocity value if the power value exceeds it.
                pow_L = (std::abs(pow_L) > kRobot::k_mMax_Vel) ? std::copysign(kRobot::k_mMax_Vel, pow_L) : pow_L;
                pow_R = (std::abs(pow_R) > kRobot::k_mMax_Vel) ? std::copysign(kRobot::k_mMax_Vel, pow_R) : pow_R;

                // Set the powers to the drive.
                kHardware::Drive_Velocity(pow_L, pow_R);

                // Delay using the supplied rate.
                pros::delay(k_sample_rate);
            }
        }
        // If the heading is positive (clockwise)
        else
        {
            
            // Code is pretty much the same as above.
            double main_radius {targ_Dist.var / kMath::Deg_To_Rad(targ_Head) },
                   left_radius {main_radius + (kRobot::k_twBase_Len / 2) },
                   right_radius {main_radius - (kRobot::k_twBase_Len / 2)};

            targ_Dist_L = kMath::Inch_To_Ticks(Inch{left_radius * kMath::Deg_To_Rad(targ_Head)});
            targ_Dist_L = kMath::Inch_To_Ticks(Inch{right_radius * kMath::Deg_To_Rad(targ_Head)});

            while ( std::abs(kMath::Inch_To_Ticks(targ_Dist)) - 
                (std::abs((aEncL.get_value() + aEncR.get_value()) / 2) ) > k_uncertainty)
            {
                err_currL = targ_Dist_L - aEncL.get_value();
                err_currR = targ_Dist_R - aEncR.get_value();

                int_L = (std::abs(err_currL) <= 0 || std::abs(err_currL) > kI_winThrsh) ? 0 : int_L + err_currL;
                int_R = (std::abs(err_currR) <= 0 || std::abs(err_currR) > kI_winThrsh) ? 0 : int_R + err_currR;

                derv_L = err_currL - err_prevL;
                derv_R = err_currR - err_prevR;

                err_prevL = err_currL;
                err_prevR = err_currL;

                // Calculate power. Left side should increase in power, right side should decrease in power.
                int pow_L = 100 + ((err_currL * kP) + (int_L * kI) + (derv_L * kD)),
                    pow_R = 100 - ((err_currR * kP) + (int_R * kI) + (derv_R * kD));

                pow_L = (std::abs(pow_L) > kRobot::k_mMax_Vel) ? std::copysign(kRobot::k_mMax_Vel, pow_L) : pow_L;
                pow_R = (std::abs(pow_R) > kRobot::k_mMax_Vel) ? std::copysign(kRobot::k_mMax_Vel, pow_R) : pow_R;

                kHardware::Drive_Velocity(pow_L, pow_R);

                pros::delay(k_sample_rate);
            }
        }
    }
    else if (targ_Dist.var)             // Straight.
    {
        // Subtract half the robot's length from the distance target depending on the distance mode.
        targ_Dist.var = (dist_mode == kAuto::k_Dist_Mode::STRAIGHT) ? targ_Dist.var : targ_Dist.var - (kRobot::k_Robot_Len / 2);

        // Keep looping as long as the robot has not reached the uncertainty threshold.
        while ( std::abs(kMath::Inch_To_Ticks(targ_Dist) - 
                (aEncL.get_value() + aEncR.get_value()) / 2) > k_uncertainty)
        {
            // Find the current error.
            err_currL = kMath::Inch_To_Ticks(targ_Dist) - ((aEncL.get_value() + aEncR.get_value()) / 2);
            err_currR = kMath::Inch_To_Ticks(targ_Dist) - ((aEncL.get_value() + aEncR.get_value()) / 2);
            
            // Find the integral, uses a ternary operator for integral windup prevention.
            int_L = (std::abs(err_currL) <= 0 || std::abs(err_currL) > kI_winThrsh) ? 0 : int_L + err_currL;
            int_R = (std::abs(err_currR) <= 0 || std::abs(err_currR) > kI_winThrsh) ? 0 : int_R + err_currR;

            // Find the derivative.
            derv_L = err_currL - err_prevL;
            derv_R = err_currR - err_prevR;

            // Assign previous error from current error.
            err_prevL = err_currL;
            err_prevR = err_currL;
            
            // Calculate power.
            int pow_L = (err_currL * kP) + (int_L * kI) + (derv_L * kD),
                pow_R = (err_currR * kP) + (int_R * kI) + (derv_R * kD);

            // Assign powers to max velocity value if the power value exceeds it.
            pow_L = (std::abs(pow_L) > kRobot::k_mMax_Vel) ? std::copysign(kRobot::k_mMax_Vel, pow_L) : pow_L;
            pow_R = (std::abs(pow_R) > kRobot::k_mMax_Vel) ? std::copysign(kRobot::k_mMax_Vel, pow_R) : pow_R;

            // Set the powers to the drive.
            kHardware::Drive_Velocity(pow_L, pow_R);

            // Delay using the supplied rate.
            pros::delay(k_sample_rate);
        }
    }
    else if (targ_Head.var)             // Point turn.
    {
        // Keep looping as long as the absolute difference between the target heading and current heading is greater than zero.
        while ( std::abs(targ_Head.var) - std::abs(sIMU.get_heading()) > 0 )
        {
            // Find the current error.
            err_currL = targ_Head.var - sIMU.get_heading();
            err_currR = targ_Head.var - sIMU.get_heading();

            // Find the derivative.
            derv_L = err_currL - err_prevL;
            derv_R = err_currR - err_prevR;

            // Assign previous error from current error.
            err_prevL = err_currL;
            err_prevR = err_currR;

            // Calculate power. On clockwise rotations, left side positive, right side negative.
            int pow_L = (err_currL * kP) + (derv_L * kD),
                pow_R = -((err_currR * kP) + (derv_R * kD));

            // Assign powers to max velocity value if the power value exceeds it.
            pow_L = (std::abs(pow_L) > kRobot::k_mMax_Vel) ? std::copysign(kRobot::k_mMax_Vel, pow_L) : pow_L;
            pow_R = (std::abs(pow_R) > kRobot::k_mMax_Vel) ? std::copysign(kRobot::k_mMax_Vel, pow_R) : pow_R;

            // Set the powers to the drive.
            kHardware::Drive_Velocity(pow_L, pow_R);

            // Delay using the supplied rate.
            pros::delay(k_sample_rate);
        }
    }
    // Clear all errors, integrals, derivatives, and targets.
    Clear_All();
}
