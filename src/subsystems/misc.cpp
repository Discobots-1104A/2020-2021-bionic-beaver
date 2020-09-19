// Discobots 1104A comp code.
// Marco Tan, Neil Sachdeva
// 
// Miscellaneous stuff defined here.

#include "subsystems/misc.h"

// Used to create a deadzone on the joysticks to prevent phantom movements.
// \param x
//      The value to be compared.
// \param y
//      The value to compare against.
// \return An integer value equal to "x" or 0.
//
auto kMisc::Check_Deadzone(int x, int y) -> int
{
    return ((std::abs(x) > y) ? x : 0);
}

// Convert inches to OSR ticks.
// \param inch
//      Inches to pass to the function.
// \return OSR ticks converted from inches.
auto kMath::Inch_To_Ticks(Inch &inch) -> int
{
    double circ { kRobot::k_twDiameter * M_PI };
    return ( std::round(inch.var / (circ / kRobot::k_OSR_Max_Ticks) ) );
}

//> Misc <//
kAuto::k_Auto_Select au_Selected_Auto{};        // Selected autonomous routine.
