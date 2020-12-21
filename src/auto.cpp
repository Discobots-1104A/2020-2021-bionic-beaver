//* stinky opcontrol code

//* headers and stuff
#include "globals.hpp"
#include "main.h"

//* functions
void live(void)
{

}

void skills(void)
{

}

/// main callback
void autonmous(void)
{
    profile_controller = okapi::AsyncMotionProfileControllerBuilder()
        .withLimits({1.0, 2.0, 10.0})
        .withOutput(chassis)
        .buildMotionProfileController();

    switch (sel_auto)
    {
        case auto_select::LIVE:
            live();
            break;
        case auto_select::SKILLS:
            skills();
            break;
    }
}