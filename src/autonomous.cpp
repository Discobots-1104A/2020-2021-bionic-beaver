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

auto Ball_Sort(const pros::vision_object_s_t &ball, int mid_pow) -> int
{
  return ( (ball.signature == op_Sorting_Colour) ? -600 : mid_pow );
}

auto Sorting_Routine() -> void
{
    while (true)
    {
        pros::vision_object_s_t ball { sVision.get_by_size(0) };
        kHardware::Pow_Intake_Convy(300, Ball_Sort(ball, 600), 600);
        pros::delay(10);
    }
}

//> Autonomous Function <//
void autonomous()
{
    // Use a switch statement to determine which auto routine to run.
    kHardware::Pow_Intake_Convy(0, 600, 600);
    pros::delay(1250);
    pros::Task sort_rout { Sorting_Routine, "Sorting Routine" };
    pros::delay(2000);
    sort_rout.suspend();
    sort_rout.remove();
}
