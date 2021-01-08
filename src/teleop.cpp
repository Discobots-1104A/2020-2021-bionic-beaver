//* stinky opcontrol code

//* headers and stuff
#include "globals.hpp"
#include "main.h"

//* global vars

int cycle_delay {0};

//* functions

/// regular move
void regular_move(int bot, int top, int itk)
{
    convey_bot.moveVelocity(bot);
    convey_top.moveVelocity(top);
    intakes.moveVelocity(itk);
}

/// driving
void driving(void)
{
    while (!(pros::competition::is_autonomous() || pros::competition::is_disabled()))
    {
        chassis->getModel()->arcade(
            controller.getAnalog(okapi::ControllerAnalog::rightY),
            controller.getAnalog(okapi::ControllerAnalog::rightX),
            10.0
        );
        pros::delay(10);
    }
}

void controls(void)
{
    int log_time {0};

    while (!(pros::competition::is_autonomous() || pros::competition::is_disabled()))
    {
        if (controller.getDigital(okapi::ControllerDigital::R1))        // index
            regular_move(600, 0, 0);
        else if (controller.getDigital(okapi::ControllerDigital::R2))   // cycle
            {
                ++log_time;
                regular_move(600, 600, (log_time >= cycle_delay) ? 600 : 0);
            }
        else if (controller.getDigital(okapi::ControllerDigital::L1))   // shoot
            regular_move(600, 600, 0);
        else if (controller.getDigital(okapi::ControllerDigital::L2))   // intake
            regular_move(0, 0, 600);
        else if (controller.getDigital(okapi::ControllerDigital::up))   // eject
            regular_move(-600, -600, -600);
        else if (controller.getDigital(okapi::ControllerDigital::down)) // convey down
            regular_move(-600, -600, 0);
        else if (controller.getDigital(okapi::ControllerDigital::left)) // itk eject fast
            regular_move(0, 0, -600);
        else if (controller.getDigital(okapi::ControllerDigital::right))    // itk eject slow
            regular_move(0, 0, -200);
        else
        {
            log_time = 0;
            regular_move(0, 0, 0);
        }
        
        pros::delay(10);
    }
}

/// main callback
void opcontrol(void)
{
    pros::Task teleop_drive {driving};
    pros::Task teleop_controls {controls};
}
