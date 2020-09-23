// Discobots 1104A comp code.
// Marco Tan, Neil Sachdeva
// 
// Code for autonomous goes here.

#include "main.h"

//> Forward Declarations of Autos <//
auto red_auto() -> void;
auto blu_auto() -> void;
auto skl_auto() -> void;

using kMath::Inch;
using kMath::Deg;
using kAuto::k_au_kP; 
using kAuto::k_au_kI; 
using kAuto::k_au_kD; 
using kAuto::k_au_I_Windup_Threshold;

//> Autonomous Function <//
void autonomous()
{
    // Use a switch statement to determine which auto routine to run.
    kHardware::Pow_Intake_Convy(0, 300, 300);
    pros::delay(2000);
    kHardware::Pow_Intake_Convy();
}
