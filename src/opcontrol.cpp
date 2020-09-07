/* Discobots 1104A comp code.
 * Marco Tan, Neil Sachdeva
 * 
 * Code for driver control goes here.
 */

#include "main.h"

// TODO: write tank drive code for the sake of options.
// TODO: turn simple drive code into assistive drive code.

/* Driving function */
auto Op_Control_Drive() -> void
{
    while (true)
    {
        int pow { kMisc::Check_Deadzone(cMaster.get_analog(cAnalog::E_CONTROLLER_ANALOG_LEFT_X), kMisc::k_cDeadzone) },
            trn { kMisc::Check_Deadzone(cMaster.get_analog(cAnalog::E_CONTROLLER_ANALOG_LEFT_Y), kMisc::k_cDeadzone) };
        
        kHardware::Drive_Voltage(pow + trn, pow - trn);
        pros::delay(10);
    }
}

/* Driver Control Function */
void opcontrol()
{
    // TODO: add intake and conveyor control
    pros::Task chassis_control { Op_Control_Drive, "Chassis Control" };
}