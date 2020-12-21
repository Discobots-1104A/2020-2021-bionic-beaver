//* stinky opcontrol code

//* headers and stuff
#include "globals.hpp"
#include "main.h"

//* functions

void selection(void)
{
    int count {0};
    while (true)
    {
        pros::lcd::print(0, "auto: %s", (count == 1) ? "skills" : "live  ");

        if (controller.getDigital(okapi::ControllerDigital::right) && count < 1)
            ++count;
        else if (controller.getDigital(okapi::ControllerDigital::left) && count > 0)
            --count;
        else if (controller.getDigital(okapi::ControllerDigital::A))
        {
            sel_auto = (count == 1) ? auto_select::SKILLS : auto_select::LIVE;
            return;
        }

        pros::delay(10);
    }
}

/// init callback
void initialize(void)
{
    pros::lcd::initialize();

    chassis = okapi::ChassisControllerBuilder()
        .withMotors({19, 20}, {-9, -10})
        .withDimensions(
            okapi::AbstractMotor::gearset::green, 
            {{4_in, 12_in}, okapi::imev5GreenTPR * (4.0/3.0)})
        .withSensors(
            okapi::ADIEncoder{'A', 'B', false},
            okapi::ADIEncoder{'B', 'C', true}
        )
        .build();

    selection();
}

/// disabled callback
void disabled(void)
{

}

/// comp init callback
void competition_initialize(void)
{

}