//* stinky opcontrol code

//* headers and stuff
#include "globals.hpp"
#include "main.h"

//* functions

/// indexing
void indexing(void)
{
    convey_bot.moveVelocity(600);
}

void cycling(void)
{
    convey_bot.moveVelocity(600);
    convey_top.moveVelocity(600);
    intakes.moveVelocity(600);
}

void shooting(void)
{
    convey_bot.moveVelocity(600);
    convey_top.moveVelocity(600);
}

void intake(void)
{
    intakes.moveVelocity(600);
}

void eject(void)
{
    convey_bot.moveVelocity(-600);
    convey_top.moveVelocity(-600);
    intakes.moveVelocity(-600);
}

void convey_down(void)
{
    convey_bot.moveVelocity(-600);
    convey_top.moveVelocity(-600);
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
    while (!(pros::competition::is_autonomous() || pros::competition::is_disabled()))
    {
        if (controller.getDigital(okapi::ControllerDigital::R1))
            indexing();
        else if (controller.getDigital(okapi::ControllerDigital::R2))
            cycling();
        else if (controller.getDigital(okapi::ControllerDigital::L1))
            shooting();
        else if (controller.getDigital(okapi::ControllerDigital::L2))
            intake();
        else if (controller.getDigital(okapi::ControllerDigital::up))
            eject();
        else if (controller.getDigital(okapi::ControllerDigital::down))
            convey_down();
        else
        {
            convey_bot.moveVelocity(0);
            convey_top.moveVelocity(0);
            intakes.moveVelocity(0);
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
