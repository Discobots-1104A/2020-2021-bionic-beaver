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
    pros::lcd::initialize();
    pros::delay(1250);
    
    Selection_Screen();
    pros::lcd::set_text(0, "AUTO SELECTED.");

    int calbr_Start{ static_cast<int>(pros::millis()) };      // Note calibration start time

    // Set the break modes to hold on the conveyor and intake motors.
    mIL.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);     // Intake left.
    mIR.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);     // Intake right.
    mCT.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);     // Conveyor top.
    mCB.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);     // Conveyor bottom.
    pros::lcd::set_text(1, "BREAK MODES SET.");

    // Tracking wheel reset.
    aEncL.reset();      // Left encoder.
    aEncR.reset();      // Right encoder.
    aEncM.reset();      // Middle encoder.
    pros::lcd::set_text(2, "ENCODERS RESET.");

    // Vision sensor initialization.
    sVision.clear_led();                                                // Clear the Vision sensor LED.
    sVision.set_wifi_mode(false);                                       // Disable WiFi capabilities.
    sVision.set_zero_point(pros::E_VISION_ZERO_TOPLEFT);                // Set the zero point to be the top-left corner.
    sVision.set_signature(kHardware::k_Colour_Sig::RED, &sigRed);       // Set the signature ID for red signature.
    sVision.set_signature(kHardware::k_Colour_Sig::BLUE, &sigBlue);     // Likewise but for blue signature.
    pros::lcd::set_text(3, "VISION CALIBRATED.");

    // IMU intialization.
    sIMU.reset();           // Start IMU calibration.
    int imu_calbr_Elaps{ 0 };               // Keep track of elapsed time.
    pros::lcd::set_text(4, "CALIBRATING IMU...");
    pros::delay(2250);
    pros::lcd::clear_line(4);

    pros::lcd::set_text(4, "IMU CALIBRATED.");
    pros::lcd::print(5, "READY. TOOK %d ms.", static_cast<int>(pros::millis()) - calbr_Start);
    pros::lcd::set_text(6, "PRESS CENTER TO CONTINUE.");
    while (pros::lcd::read_buttons() != LCD_BTN_CENTER) { pros::delay(5); };
    pros::lcd::clear();
}

auto Select_Auto(int selected) -> void;

//> Selection Screen <//
auto Selection_Screen() -> void
{
    //TODO: Fix Selection_Screen() code cuz its doodoo.
    // Initialize and give 1 second to do so.

    // Create temp int for selection.
    int cur_select {0};
    pros::lcd::set_text(0, "SELECT SORT:");

    while (true)
    {
        // Change what's displayed based on value of cur_select
        if (cur_select == 0)
        {
            pros::lcd::print(1, "SORT: BLUE");
        }
        else if (cur_select == 1)
        {
            pros::lcd::print(1, "SORT: RED ");
        }
        else if (cur_select == 2)
        {
            pros::lcd::print(1, "SORT: BLUE");
        }

        // Scrolling selection.
        if (pros::lcd::read_buttons() == LCD_BTN_LEFT)          // Scroll left.
            { if (cur_select > 0) { --cur_select; } }
        else if (pros::lcd::read_buttons() == LCD_BTN_RIGHT)    // Scrll right.
            { if (cur_select < 2) { ++cur_select; } }
        else if (pros::lcd::read_buttons() == LCD_BTN_CENTER)   // Confirm selection.
        {
            // Assign selected autons and sorting colour based on value of cur_select
            pros::lcd::clear_line(0); pros::lcd::clear_line(1); pros::lcd::clear_line(2);
            pros::delay(1000);
            Select_Auto(cur_select);
            break;
        }

        pros::delay(300);
    }
}

auto Select_Auto(int selected) -> void
{
    switch (selected)
    {
    // Red autonomous, sort blue balls.
    case 0 :
        op_Sorting_Colour = kHardware::k_Colour_Sig::BLUE;
        break;
    // Blue autonomous, sort red balls.
    case 1 :
        op_Sorting_Colour = kHardware::k_Colour_Sig::RED;
        break;
    // Skills autonomous, sort blue balls.
    case 2 :
        op_Sorting_Colour = kHardware::k_Colour_Sig::BLUE;
        break;
    }
}
