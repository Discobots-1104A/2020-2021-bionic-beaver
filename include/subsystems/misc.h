/* Discobots 1104A comp code.
 * Marco Tan, Neil Sachdeva
 * 
 * Miscellaneous stuff declared here.
 */

#ifndef MISC_H
#define MISC_H

#include "main.h"

namespace misc
{
    /* Miscellaneous Functions */

    inline auto Check_Deadzone(int x, int y) -> int;

    /* Miscellaneous Constants */
    inline constexpr int k_cDeadzone{ 10 };     // Controller deadzone constant.
    
}

#endif