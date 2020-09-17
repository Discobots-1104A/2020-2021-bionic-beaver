// Discobots 1104A comp code.
// Marco Tan, Neil Sachdeva
// 
// Miscellaneous stuff defined here.

#include "subsystems/misc.h"

// Used to create a deadzone on the joysticks to prevent phantom movements.
// \param x
//      An integer value to be compared.
// \param y
//      An integer value to compare against.
// \return An integer value equal to "x" or 0.
//
auto kMisc::Check_Deadzone(int x, int y) -> int
{
    return ((std::abs(x) > y) ? x : 0);
}

//> Misc <//
kAuton::k_Auto_Select au_Selected_Auto{}; 