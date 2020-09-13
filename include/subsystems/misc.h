// Discobots 1104A comp code.
// Marco Tan, Neil Sachdeva
// 
// Miscellaneous stuff declared here.

#ifndef MISC_H
#define MISC_H

#include "main.h"

//> Misc namespace <//
namespace kMisc     // Miscellaneous namespace.
{
    //> Miscellaneous Functions <//

    auto Check_Deadzone(int x, int y) -> int;

    //> Miscellaneous Constants <//
    inline constexpr int k_cDeadzone{ 10 };     // Controller deadzone constant.
    enum k_Auto_Select                          // Autonomous selection enum.
    {      
        RED,               
        BLUE,
        SKILLS
    };

    k_Auto_Select au_Selected_Auto;             // Selected autonomous routine.
}

//> Math namespace <//
namespace kMath     // Math namespace.                           
{
    inline constexpr int k_OSR_Max_Ticks { 360 };       // Max optical shaft encoder ticks.
    inline constexpr int k_mMax_Vel { 200 };            // Max motor velocity.
    inline constexpr double k_mGear_Ratio { 1.75 };     // Gear ratio if it is made later.
    inline constexpr double k_twDiameter { 2.75 };      // Tracking wheel diameter.
    inline constexpr double k_Wheelbase_Len { 0.0 };    // Wheelbase length in inches.
    inline constexpr double k_twBase_Len { 12.0 };      // Length between both side tracking wheels
    inline constexpr double k_mtwLen { 6.5 };           // Length from center of robot to middle tracking wheel.
    inline constexpr double k_Robot_Len { 17.5 };       // Robot length.
    inline constexpr double k_Robot_Wid { 15.56 };      // Robot width.
    constexpr double k_Pi() { return std::acos(-1); }   // Returns pi.
}

#endif