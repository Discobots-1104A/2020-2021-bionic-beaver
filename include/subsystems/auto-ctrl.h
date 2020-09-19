// Discobots 1104A comp code.
// Marco Tan, Neil Sachdeva
// 
// Autonomous algorithms are declared here.

#include "main.h"

#ifndef AUTO_CTRL_H
#define AUTO_CTRL_H

//> Autonomous PID controller class.
class Auto_PID      // PID class.
{
private:
    //> Private Variables and Constants <//
    const double kP, kI, kD;            // PID Constants.
    const double kI_winThrsh;           // Integral windup threshold.
    const int k_sample_rate;            // Sample rate in milliseconds.
    kAuto::k_Dist_Mode dist_mode;       // Whether to treat distance as a straight line or an arc length.
    double err_currL{}, err_currR{};    // Current errors.
    double err_prevL{}, err_prevR{};    // Previous errors.
    kMath::Deg targ_Head{};             // Heading target.
    kMath::Inch targ_Dist{};            // Distance target.

    // Clear errors and targets.
    auto Clear_All() -> void
    {
        err_currL = 0;  err_currR = 0;
        err_prevL = 0;  err_prevR = 0;
        targ_Head = {}; targ_Dist = {};
    }

public:
    // Constructor

    Auto_PID(double P = 0.0, double I = 0.0, double D = 0.0, 
            double i_winThrsh = 0.0, int sample_rate = 15,
            kAuto::k_Dist_Mode mode = kAuto::k_Dist_Mode::ARC_LENGTH);


    //> Public Functions <//

    auto Set_Target(const kMath::Deg &head) -> Auto_PID&;
    auto Set_Target(const kMath::Inch &dist) -> Auto_PID&;
    auto Set_Dist_Mode(const kAuto::k_Dist_Mode &mode) -> Auto_PID&;
    auto Drive() -> void;

};

#endif // AUTO_CTRL_H
