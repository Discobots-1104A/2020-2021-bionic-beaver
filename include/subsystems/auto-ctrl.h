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
    double kP, kI, kD;                  // PID Constants.
    double kI_winThrsh;                 // Integral windup threshold.
    const int k_sample_rate;            // Sample rate in milliseconds.
    const int k_uncertainty;            // By how many ticks the controller is allowed to be off.
    kAuto::k_Dist_Mode dist_mode;       // Whether to treat distance as a straight line or an arc length.
    int err_currL{}, err_currR{};       // Current errors.
    int err_prevL{}, err_prevR{};       // Previous errors.
    int int_L{}, int_R{};               // Integrals.
    int derv_L{}, derv_R{};             // Derivatives
    kMath::Deg targ_Head{};             // Heading target.
    kMath::Inch targ_Dist{};            // Distance target.

    // Clear errors, integrals, derivatives, and targets.
    auto Clear_All() -> void
    {
        err_currL = 0;  err_currR = 0;
        err_prevL = 0;  err_prevR = 0;
        int_L = 0;      int_R = 0;
        derv_L = 0;     derv_R = 0;
        targ_Head = {}; targ_Dist = {};
    }

    // Clear errors, integrals, derivatives, reset tracking wheels.
    auto Clear_No_Targets() -> void
    {
        err_currL = 0;  err_currR = 0;
        err_prevL = 0;  err_prevR = 0;
        int_L = 0;      int_R = 0;
        derv_L = 0;     derv_R = 0;
        aEncL.reset();  aEncR.reset();  aEncM.reset();
    }

public:
    // Constructor

    Auto_PID(double P = 0.0, double I = 0.0, double D = 0.0, 
            double i_winThrsh = 300.0, int sample_rate = 15, int uncertainty = 5,
            kAuto::k_Dist_Mode mode = kAuto::k_Dist_Mode::ARC_LENGTH);


    //> Public Functions <//

    auto Set_Target(const kMath::Deg &head) -> Auto_PID&;
    auto Set_Target(const kMath::Inch &dist) -> Auto_PID&;
    auto Set_Dist_Mode(const kAuto::k_Dist_Mode &mode) -> Auto_PID&;
    auto Set_PID(double P, double I, double D, double i_winThrsh = 300.0) -> Auto_PID&;
    auto Drive() -> void;

};

#endif // AUTO_CTRL_H
