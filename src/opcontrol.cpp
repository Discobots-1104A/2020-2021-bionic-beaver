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

        int pow { kMisc::Check_Deadzone(cMaster.get_analog(cAnalog::E_CONTROLLER_ANALOG_RIGHT_X), kMisc::k_cDeadzone) },
            trn { kMisc::Check_Deadzone(cMaster.get_analog(cAnalog::E_CONTROLLER_ANALOG_RIGHT_Y), kMisc::k_cDeadzone) };

        
        kHardware::Drive_Voltage(pow + trn, pow - trn);
        pros::delay(10);
    }
}
auto Op_Control_Intk_Convy() -> void
{
    while(true)
    {
        int intake_pow{};
        int convy_pow{};

        if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_R2))
            intake_pow = 600;
        else if (cMaster.get_analog(cAnalog::E_CONTROLLER_ANALOG_LEFT_Y))
            intake_pow = -600;
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_UP))
            convy_pow = 600;
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_DOWN))
            convy_pow = -600;
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_R1))
        {
            intake_pow = -600;
            convy_pow = -600;
        }
        else
        {
            intake_pow = 0;
            convy_pow = 0;
        }
        kHardware::Pow_Intake_Convy(intake_pow, convy_pow);
        pros::delay(10);
    }
}
/* Driver Control Function */
void opcontrol()
{
    // TODO: check if Neil added the task correctly
    pros::Task intake_conveyor_control { Op_Control_Intk_Convy, "Intake Conveyor Control"};
    pros::Task chassis_control { Op_Control_Drive, "Chassis Control" };
}