// Discobots 1104A comp code.
// Marco Tan, Neil Sachdeva
// 
// Code for driver control goes here.

#include "main.h"


//> Forward Declarations <//
auto Macro_Indexing() -> void;      // Macro for indexing.
auto Macro_Cycling()  -> void;      // Macro for cycling.
auto Macro_Shoot()    -> void;      // Macro for shooting.
auto Macro_Intakes()  -> void;      // Macro for intakes.
auto Macro_Outtake()  -> void;      // Emergency macro for spitting out everything.
auto Macro_Convy_Rev()-> void;      // Emergency macro, only for conveyor motors.

//> Global Variables <//
pros::Task mcr_indexing { Macro_Indexing, "Macro: Indexing" };      // Indexing macro task.
pros::Task mcr_cycling { Macro_Cycling,  "Macro: Cycling" };        // Cycling macro task.
pros::Task mcr_shoot { Macro_Shoot, "Macro: Shoot" };               // Shooting macro task.
pros::Task mcr_intakes { Macro_Intakes, "Macro: Intakes" };         // Intake macro task.
pros::Task mcr_outtake {Macro_Outtake, "Macro: Outtake" };          // Emergency macro task.
pros::Task mcr_convy_rev { Macro_Convy_Rev, "Macro: Conv. Rev." };  // Emergency macro task 2.
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
        pros::delay(5);
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
        if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_R1))             // Indexing, Button R1
            mcr_indexing.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_R2))        // Cycling, Button R2
            mcr_cycling.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_L1))        // Shooting, Button L1
            mcr_shoot.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_L2))        // Intakes, Button L2
            mcr_intakes.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_UP))        // Emergency macro, Button up
            mcr_outtake.notify();
        else if (cMaster.get_digital(cDigital::E_CONTROLLER_DIGITAL_DOWN))      // Emergency macro 2, button down
            mcr_convy_rev.notify();
        else if (cMaster.get_digital_new_press(cDigital::E_CONTROLLER_DIGITAL_RIGHT))     // Toggle auto pooping, Button right
        {
            auto_pooping = !auto_pooping;   // This doesn't notify, but toggles the pooping function.
            if (auto_pooping)
                cMaster.rumble("...");
            else
                cMaster.rumble("--");
        }
        else
            kHardware::Pow_Intake_Convy();  // If no buttons pressed, turn off all the intake and conveyor motors.

        // Delay to not hog resources.
        pros::delay(5);
    }
}

auto Debug() -> void
{
    while (true)
    {
        pros::vision_object_s_t ball1 { sVision.get_by_size(0) };
        pros::lcd::print(0, "ball width:%d", ball1.width);
        pros::lcd::print(1, "ball height:%d", ball1.height);
        pros::delay(5);
    }
}

//> Driver Control Function <//
void opcontrol()
{
    // Intake and Conveyor control task.
    pros::Task intake_conveyor_control { Op_Control_Intk_Convy, "Intake Conveyor Control"};
    // Chassis control task.
    pros::Task chassis_control { Op_Control_Drive, "Chassis Control" };
    // Debug
    //pros::Task debug { Debug, "Debug" };
}


//> Helper Functions <//

auto Ball_Sort(const pros::vision_object_s_t &ball, int mid_pow) -> int
{
  return ( (ball.width > 50) ? -600 : mid_pow );
}

auto Macro_Indexing() -> void
{
    while (mcr_indexing.notify_take(true, TIMEOUT_MAX))
    {
        pros::vision_object_s_t ball { sVision.get_by_sig(0, kHardware::k_Colour_Sig::BLUE) };

        if (auto_pooping)
            kHardware::Pow_Intake_Convy(600, Ball_Sort(ball, 0), 600);
        else
            kHardware::Pow_Intake_Convy(600, 0, 600);
    }
}

auto Macro_Cycling() -> void
{
    while (mcr_cycling.notify_take(true, TIMEOUT_MAX))
    {
        pros::vision_object_s_t ball { sVision.get_by_sig(0, kHardware::k_Colour_Sig::BLUE) };

        if (auto_pooping)
            kHardware::Pow_Intake_Convy(600, Ball_Sort(ball, 600), 600);
        else
            kHardware::Pow_Intake_Convy(600, 600, 600);
    }
}
//> Shooting <//
auto Macro_Shoot() -> void
{
    while (mcr_shoot.notify_take(true, TIMEOUT_MAX))
    {
        kHardware::Pow_Intake_Convy(0, 600, 600);
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

//> Conveyor Reversal <//
auto Macro_Convy_Rev() -> void
{
    while (mcr_convy_rev.notify_take(true, TIMEOUT_MAX))
    {
        kHardware::Pow_Intake_Convy(0, -600, -600);
    }
}
