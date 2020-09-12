// Discobots 1104A comp code.
// Marco Tan, Neil Sachdeva
// 
// Code for driver control goes here.

#include "main.h"

// TODO: write tank drive code for the sake of options.
// TODO: turn simple drive code into assistive drive code.

//> Forward Declarations <//
auto Macro_Indexing() -> void;          // Macro for indexing.
auto Macro_Cycling()  -> void;          // Macro for cycling.
auto Macro_Shoot()    -> void;          // Macro for shooting.
auto Macro_Intakes()  -> void;          // Macro for intakes.
auto Macro_Outtake()  -> void;          // Emergency macro for spitting out everything.

//> Global Variables <//
pros::Task mcr_indexing { Macro_Indexing, "Macro: Indexing" };      // Indexing macro task.
pros::Task mcr_cycling { Macro_Cycling,  "Macro: Cycling" };        // Cycling macro task.
pros::Task mcr_shoot { Macro_Shoot, "Macro: Shoot" };               // Shooting macro task.
pros::Task mcr_intakes { Macro_Intakes, "Macro: Intakes" };         // Intake macro task.
pros::Task mcr_outtake {Macro_Outtake, "Macro: Outtake" };          // Emergency macro task.
bool auto_pooping { true };       // Pooping toggle. Default true.


//> Main Functions <//

//> Driving function <//
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

//> Main intake and conveyor function <//
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
        else
            kHardware::Pow_Intake_Convy();
        
        pros::delay(10);
    }
}

//> Driver Control Function <//
void opcontrol()
{
    pros::Task intake_conveyor_control { Op_Control_Intk_Convy, "Intake Conveyor Control"};
    pros::Task chassis_control { Op_Control_Drive, "Chassis Control" };
}


//> Helper Functions <//

//> Indexing <//
auto Macro_Indexing() -> void
{
    while (mcr_indexing.notify_take(true, TIMEOUT_MAX))
    {
        //TODO: write indexing function when i can implement it
    }
}

//> Cycling <//
auto Macro_Cycling() -> void
{
    while (mcr_cycling.notify_take(true, TIMEOUT_MAX))
    {
        //TODO: rewrite cycling function to use vision sensor for automatic pooping
        kHardware::Pow_Intake_Convy(600, 600, 600);
    }
}

//> Shooting <//
auto Macro_Shoot() -> void
{
    while (mcr_shoot.notify_take(true, TIMEOUT_MAX))
    {
        //TODO: write shooting function when i can implement it
    }
}

//> Intakes <//
auto Macro_Intakes() -> void
{
    while (mcr_intakes.notify_take(true, TIMEOUT_MAX))
    {
        kHardware::Pow_Intake_Convy(600);
    }
}

//> Outtake <//
auto Macro_Outtake() -> void
{
    while (mcr_outtake.notify_take(true, TIMEOUT_MAX))
    {
        kHardware::Pow_Intake_Convy(-600, -600, -600);
    }
}