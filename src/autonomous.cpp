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
    switch (au_Selected_Auto)
    {
    case kAuto::k_Auto_Select::RED:
        red_auto();
        break;
    case kAuto::k_Auto_Select::BLUE:
        blu_auto();
        break;
    case kAuto::k_Auto_Select::SKILLS:
        skl_auto();
        break;
    }
}

//> Red Auto <//
auto red_auto() -> void
{
    // Create Auto_PID object "test"
    // Supplying constructor with the constants in kAuto namespace
    Auto_PID test {k_au_kP, k_au_kI, k_au_kD, k_au_I_Windup_Threshold};

    // Try moving back and forth.
    test.Set_Target(Inch{20}).Drive();
    pros::delay(500);
    test.Set_Target(Inch{-20}).Drive();
    pros::delay(1000);

    // Try in place turn
    test.Set_Target(Deg{90}).Drive();
    pros::delay(500);
    test.Set_Target(Deg{0}).Drive();
    pros::delay(1000);
    test.Set_Target(Deg{-90}).Drive();
    pros::delay(500);
    test.Set_Target(Deg{0}).Drive();
    pros::delay(1000);

    // Try swerve turn.
    test.Set_Target(Inch{20}).Set_Target(Deg{45}).Drive();
    pros::delay(500);
    test.Set_Target(Inch{-20}).Set_Target(Deg{45}).Drive();
    pros::delay(500);
    test.Set_Target(Inch{20}).Set_Target(Deg{-45}).Drive();
    pros::delay(500);
    test.Set_Target(Inch{-20}).Set_Target(Deg{-45}).Drive();
    pros::delay(1000);
}

//> Blue Auto <//
auto blu_auto() -> void
{

}

//> Skills Auto<//
auto skl_auto() -> void
{

}
