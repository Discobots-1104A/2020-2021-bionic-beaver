// Discobots 1104A comp code.
// Marco Tan, Neil Sachdeva
// 
// Code for driver control goes here.

#include "main.h"


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
    // Main loop.
    while (true)
    {
        // Create and initialize integers with values from the joystick.
        int pow { kMisc::Check_Deadzone(cMaster.get_analog(cAnalog::E_CONTROLLER_ANALOG_RIGHT_Y), kMisc::k_cDeadzone) },
            trn { kMisc::Check_Deadzone(cMaster.get_analog(cAnalog::E_CONTROLLER_ANALOG_RIGHT_X), kMisc::k_cDeadzone) };

        // Assign arcade drive voltages to the wheels.
        kHardware::Drive_Voltage(pow + trn, pow - trn);
        // Delay to not hog resources.
        pros::delay(10);
    }
}

//> Main intake and conveyor function <//
auto Op_Control_Intk_Convy() -> void
{
    // Main loop.
    while (true)
    {
        // Big elif block for each button.
        // Each button will notify one of the macro tasks to perform said action.
        if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_R1))             // Button R1
            mcr_indexing.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_R2))        // Button R2
            mcr_cycling.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_L1))        // Button L1
            mcr_shoot.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_L2))        // Button L2
            mcr_intakes.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_UP))        // Button up
            mcr_outtake.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_RIGHT))     // Button right
            auto_pooping = !auto_pooping;   // This doesn't notify, but toggles the pooping function.
        else
            kHardware::Pow_Intake_Convy();  // If no buttons pressed, turn off all the intake and conveyor motors.
            
        // Delay to not hog resources.
        pros::delay(10);
    }
}

//> Driver Control Function <//
void opcontrol()
{
    // Intake and Conveyor control task.
    pros::Task intake_conveyor_control { Op_Control_Intk_Convy, "Intake Conveyor Control"};
    // Chassis control task.
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