/* Discobots 1104A comp code.
 * Marco Tan, Neil Sachdeva
 * 
 * Code for driver control goes here.
 */

#include "main.h"

// TODO: write tank drive code for the sake of options.
// TODO: turn simple drive code into assistive drive code.

/* Forward Declarations */
auto Macro_Indexing() -> void;
auto Macro_Cycling()  -> void;
auto Macro_Shoot()    -> void;
auto Macro_Intakes()  -> void;
auto Macro_Outtake()   -> void;

/* Global Variables */
pros::Task mcr_indexing { Macro_Indexing, "Macro: Indexing" };
pros::Task mcr_cycling { Macro_Cycling,  "Macro: Cycling" };
pros::Task mcr_shoot { Macro_Shoot, "Macro: Shoot" };
pros::Task mcr_intakes { Macro_Intakes, "Macro: Intakes" };
pros::Task mcr_outtake {Macro_Outtake, "Macro: Outtake" };
bool auto_pooping { false };       // Pooping toggle.


/* Main Functions */

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

/* Main intake and conveyor function */
auto Op_Control_Intk_Convy() -> void
{
    while (true)
    {
        if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_R1))
            mcr_indexing.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_R2))
            mcr_cycling.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_L1))
            mcr_shoot.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_L2))
            mcr_intakes.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_UP))
            mcr_outtake.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_RIGHT))
            auto_pooping = !auto_pooping;
        
        pros::delay(10);
    }
}

/* Driver Control Function */
void opcontrol()
{
    pros::Task intake_conveyor_control { Op_Control_Intk_Convy, "Intake Conveyor Control"};
    pros::Task chassis_control { Op_Control_Drive, "Chassis Control" };
}


/* Helper Functions */

/* Indexing */
auto Macro_Indexing() -> void
{
    while (mcr_indexing.notify_take(true, TIMEOUT_MAX))
    {

    }
}

/* Cycling */
auto Macro_Cycling() -> void
{
    while (mcr_cycling.notify_take(true, TIMEOUT_MAX))
    {

    }
}

/* Shooting */
auto Macro_Shoot() -> void
{
    while (mcr_shoot.notify_take(true, TIMEOUT_MAX))
    {

    }
}

/* Intakes */
auto Macro_Intakes() -> void
{
    while (mcr_intakes.notify_take(true, TIMEOUT_MAX))
    {

    }
}

/* Outtake */
auto Macro_Outtake() -> void
{
    while (mcr_outtake.notify_take(true, TIMEOUT_MAX))
    {

    }
}