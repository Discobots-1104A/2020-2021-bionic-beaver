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
    const double kP, kI, kD;            // PID Constants.
    const double kI_winThrsh;           // Integral windup threshold.
    kAuto::k_Dist_Mode dist_mode;       // Whether to treat distance as a straight line or an arc length.
    double err_currL, err_currR;        // Current errors.
    double err_prevL, err_prevR;        // Previous errors.
    kMath::Deg targ_Head;               // Heading target.
    kMath::Inch targ_Dist;              // Distance target.

public:
    // Constructor

    Auto_PID(double P = 0.0, double I = 0.0, double D = 0.0, 
            double i_winThrsh = 0.0, 
            kAuto::k_Dist_Mode mode = kAuto::k_Dist_Mode::ARC_LENGTH);


    //> Functions <//

    auto Set_Target(const kMath::Deg &head) -> Auto_PID&;
    auto Set_Target(const kMath::Inch &dist) -> Auto_PID&;
    auto Set_Dist_Mode(const kAuto::k_Dist_Mode &mode) -> Auto_PID&;
    auto Drive() -> void;

};

#endif // AUTO_CTRL_H
