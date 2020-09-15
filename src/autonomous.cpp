// Discobots 1104A comp code.
// Marco Tan, Neil Sachdeva
// 
// Code for autonomous goes here.

#include "main.h"

//> Forward Declarations of Autos <//
auto red_auto() -> void;
auto blu_auto() -> void;
auto skl_auto() -> void;

//> Autonomous Function <//
void autonomous()
{
    switch (kMisc::au_Selected_Auto)
    {
    case kMisc::k_Auto_Select::RED:
        red_auto();
        break;
    case kMisc::k_Auto_Select::BLUE:
        blu_auto();
        break;
    case kMisc::k_Auto_Select::SKILLS:
        skl_auto();
        break;
    }
}

//> Red Auto <//
auto red_auto() -> void
{

}

//> Blue Auto <//
auto blu_auto() -> void
{

}

//> Skills Auto<//
auto skl_auto() -> void
{

}