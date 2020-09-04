/* Discobots 1104A comp code.
 * Marco Tan, Neil Sachdeva
 * 
 * Miscellaneous stuff defined here.
 */

#include "subsystems/misc.h"


inline auto Check_Deadzone(int x, int y) -> int
{
    return ((x > y) ? x : 0);
}