/* Discobots 1104A comp code.
 * Marco Tan, Neil Sachdeva
 * 
 * Miscellaneous stuff defined here.
 */

#include "subsystems/misc.h"

/* Compare x to y. If x is bigger, return x. Otherwise, return 0.
 * \param x
 *      An integer value to be compared.
 * \param y
 *      An integer value to compare against.
 */
auto kMisc::Check_Deadzone(int x, int y) -> int
{
    return ((std::abs(x) > y) ? x : 0);
}