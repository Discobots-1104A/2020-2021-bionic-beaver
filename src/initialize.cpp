// Discobots 1104A comp code.
// Marco Tan, Neil Sachdeva
// 
// Code for initialization goes here.

#include "main.h"

//> Disabled Function <//
void disabled()
{

}

//> Comp Initialization Function <//
void competition_initialize()
{

}

// Forward declaration of Selection_Screen()
auto Selection_Screen() -> void;

//> Initialize Function <//
void initialize()
{
    // TODO: create auton selector
    // TODO: add necessary initialization
    // Start LLEMU Selector screen
    Selection_Screen();
    pros::lcd::set_text(0, "AUTO SELECTED.");

    // Set the break modes to hold on the conveyor and intake motors.
    mIL.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);     // Intake left.
    mIR.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);     // Intake right.
    mCT.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);     // Conveyor top.
    mCB.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);     // Conveyor bottom.
    pros::lcd::set_text(1, "BREAK MODES SET.");

    // Vision sensor initialization.
    sVision.clear_led();                                                // Clear the Vision sensor LED.
    sVision.set_wifi_mode(false);                                       // Disable WiFi capabilities.
    sVision.set_zero_point(pros::E_VISION_ZERO_TOPLEFT);                // Set the zero point to be the top-left corner.
    sVision.set_signature(kHardware::k_Colour_Sig::RED, &sigRed);       // Set the signature ID for red signature.
    sVision.set_signature(kHardware::k_Colour_Sig::BLUE, &sigBlue);     // Likewise but for blue signature.
    pros::lcd::set_text(2, "VISION CALIBRATED.");

    // IMU intialization.
    sIMU.reset();           // Start IMU calibration.
    pros::delay(2250);      // Give it 2.25 seconds to calibrate.
    pros::lcd::set_text(3, "IMU CALIBRATED.");
    pros::lcd::set_text(4, "READY.");
    pros::delay(1000);
    pros::lcd::clear();
}

//> Selection Screen <//
auto Selection_Screen() -> void
{
    // Initialize and give 1 second to do so.
    pros::lcd::initialize();
    pros::delay(1000);

    // Create temp int for selection.
    int cur_select {0};
    pros::lcd::set_text(0, "Select auto:");

    while (true)
    {
        // Change what's displayed based on value of cur_select
        switch (cur_select)
        {
        case 0 :
            pros::lcd::print(1, "AUTO: RED  ");
            pros::lcd::print(2, "SORT: BLUE");
            break;
        case 1 :
            pros::lcd::print(1, "AUTO: BLUE ");
            pros::lcd::print(2, "SORT: RED ");
            break;
        case 2 :
            pros::lcd::print(1, "AUTO: SKILLS");
            pros::lcd::print(2, "SORT: BLUE");
            break;
        }

        // Scrolling selection.
        if (pros::lcd::read_buttons() == LCD_BTN_LEFT)          // Scroll left.
            if (cur_select > 0) { --cur_select; }
        else if (pros::lcd::read_buttons() == LCD_BTN_RIGHT)    // Scroll right.
            if (cur_select < 2) { ++cur_select; }
        else if (pros::lcd::read_buttons() == LCD_BTN_CENTER)   // Confirm selection.
        {
            // Assign selected autons and sorting colour based on value of cur_select
            switch (cur_select)
            {
            // Red autonomous, sort blue balls.
            case 0 :
                kAuton::au_Selected_Auto = kAuton::k_Auto_Select::RED;
                kHardware::op_Sorting_Colour = kHardware::k_Colour_Sig::BLUE;
                pros::lcd::clear();
                return;
            // Blue autonomous, sort red balls.
            case 1 :
                kAuton::au_Selected_Auto = kAuton::k_Auto_Select::BLUE;
                kHardware::op_Sorting_Colour = kHardware::k_Colour_Sig::RED;
                pros::lcd::clear();
                return;
            // Skills autonomous, sort blue balls.
            case 2 :
                kAuton::au_Selected_Auto = kAuton::k_Auto_Select::SKILLS;
                kHardware::op_Sorting_Colour = kHardware::k_Colour_Sig::BLUE;
                pros::lcd::clear();
                return;
            }
        }
    }
}