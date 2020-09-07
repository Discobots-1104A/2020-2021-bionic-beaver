/* Discobots 1104A comp code.
 * Marco Tan, Neil Sachdeva
 * 
 * Miscellaneous stuff declared here.
 */

#ifndef MISC_H
#define MISC_H

#include "main.h"

/* Misc namespace */
namespace kMisc
{
    /* Miscellaneous Functions */

    auto Check_Deadzone(int x, int y) -> int;

    /* Miscellaneous Constants */
    inline constexpr int k_cDeadzone{ 10 };     // Controller deadzone constant.
    enum k_Auto_Select                          // Autonomous selection enum.
    {      
        RED,               
        BLUE,
        SKILLS
    };
}

/* Math namespace */
namespace kMath                                  
{
    inline constexpr int k_OSR_Max_Ticks { 360 };       // Max optical shaft encoder ticks.
    inline constexpr int k_mMax_Vel { 200 };            // Max motor velocity.
    inline constexpr double k_mGear_Ratio { 0.0 };      // Gear ratio if it is made later.
    inline constexpr double k_Pi { 3.141592653589793 }; // Close approximation to pi.
    inline constexpr double k_twDiameter { 2.75 };      // Tracking wheel diameter.
    inline constexpr double k_Wheelbase_Len { 0.0 };    // Wheelbase length.
    inline constexpr double k_mtwLen { 0.0 };           // Length from center of robot to middle tracking wheel.
    inline constexpr double k_Robot_Len { 0.0 };        // Robot length.
    inline constexpr double k_Robot_Wid { 0.0 };        // Robot width.
}

#endif