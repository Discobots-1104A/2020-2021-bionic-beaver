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

        int pow { kMisc::Check_Deadzone(cMaster.get_analog(cAnalog::E_CONTROLLER_ANALOG_RIGHT_Y), kMisc::k_cDeadzone) },
            trn { kMisc::Check_Deadzone(cMaster.get_analog(cAnalog::E_CONTROLLER_ANALOG_RIGHT_X), kMisc::k_cDeadzone) };

        
        kHardware::Drive_Voltage(pow + trn, pow - trn);
        pros::delay(10);
    }
}
auto Op_Control_Intk_Convy() -> void
{
    while(true)
    {
        int intake_pow{};
        int convy_pow1{};
        int convy_pow2{};

        if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_R2)) //intaking
            intake_pow = -600;
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_L2)) //outaking
            intake_pow = 600;
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_UP)) //conveyor in
        {
            convy_pow1 = 600;
            convy_pow2 = 600;
        }
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_DOWN)) //conveyor out
        {
            convy_pow1 = -600;
            convy_pow2 = -600;
        }   
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_R1)) //cycling in
        {
            intake_pow = -600;
            convy_pow1 = -600;
            convy_pow2 = -600;
        }
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_RIGHT)) //cycling out
        {
            intake_pow = 600;
            convy_pow1 = 600;
            convy_pow2 = 600;
        }
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_L1)) //pooping while intaking
        {
            intake_pow = -600;
            convy_pow1 = -600;
            convy_pow2 = 600;
        }
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_LEFT)) //just pooping 
        {
            convy_pow1 = -600;
            convy_pow2 = 600;
        }
        else //nothing happens
        {
            intake_pow = 0;
            convy_pow1 = 0;
            convy_pow2 = 0;
        }
        kHardware::Pow_Intake_Convy(intake_pow, convy_pow1, convy_pow2);
        pros::delay(10);
    }
}
/* Driver Control Function */
void opcontrol()
{
    // TODO: 
    pros::Task intake_conveyor_control { Op_Control_Intk_Convy, "Intake Conveyor Control"};
    pros::Task chassis_control { Op_Control_Drive, "Chassis Control" };
}