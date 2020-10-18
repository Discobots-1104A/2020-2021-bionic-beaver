//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Main initialization code.


//* Headers
#include "main.h"   // Main header.


//* Functions

// Screen clear function b/c the native one segfaults stuff for some reason.
void clear_screen()
{
    // Iterate through all the lines on the screen and clear the line.
    for (auto i{0}; i < k_Hardware::h_llemu_lines; ++i)
        pros::lcd::clear_line(i);
}

// Selects autos and ball sorting colour
void selector_screen()
{
    // Text to clarify controls.
    pros::lcd::print(0, "use controller to select.");
    pros::lcd::print(1, "left & right scroll, 'A' to select");

    // Current selection.
    int current_sel {0};
    // Infinite loop.
    while (true)
    {
        // Printing text on screen & selecting sorting ID.
        switch (current_sel)
        {
        case 0:
            pros::lcd::print(2, "sort col: red  ");     // Sort for red.
            h_sorted_ball_id = h_sVision_IDs::RED_ID;
            break;
        case 1:
            pros::lcd::print(2, "sort col: blue ");     // Sort for blue.
            h_sorted_ball_id = h_sVision_IDs::BLUE_ID;
            break;
        case 2:
            pros::lcd::print(2, "sort col: skills");    // Sort for skills colour (blue).
            h_sorted_ball_id = h_sVision_IDs::BLUE_ID;
            break;
        }

        // Associate each button used on the controller to a selection function.
        if (h_obj_ctrl.get_digital_new_press(h_ctrl_digital::E_CONTROLLER_DIGITAL_LEFT))        // Scroll left.
            { if (current_sel > 0) {--current_sel;} }
        else if (h_obj_ctrl.get_digital_new_press(h_ctrl_digital::E_CONTROLLER_DIGITAL_RIGHT))  // Scroll right.
            { if (current_sel < 2) {++current_sel;} }
        else if (h_obj_ctrl.get_digital_new_press(h_ctrl_digital::E_CONTROLLER_DIGITAL_A))      // Select.
        { 
            h_obj_ctrl.rumble("...");   // Rumble to let you know you selected.
            break;                      // Exit the infinite loop.
        }

        pros::delay(10);    // Delay b/c the LCD can't refresh faster than this.
    }

    // Reset current_sel.
    current_sel = 0;
    // Infinite loop.
    while (true)
    {
        // Printing text on screen & selecting auto routine.
        switch (current_sel)
        {
        case 0:
            pros::lcd::print(3, "auto: red  ");     // Red routine.
            a_routine = a_Autonomous_Routine::RED;
            break;
        case 1:
            pros::lcd::print(3, "auto: blue ");     // Blue routine.
            a_routine = a_Autonomous_Routine::BLUE;
            break;
        case 2:
            pros::lcd::print(3, "auto: skills");    // Skills routine.
            a_routine = a_Autonomous_Routine::SKILLS;
            break;
        }

        // Associate each button used on the controller to a selection function.
        if (h_obj_ctrl.get_digital_new_press(h_ctrl_digital::E_CONTROLLER_DIGITAL_LEFT))        // Scroll left.
            { if (current_sel > 0) {--current_sel;} }
        else if (h_obj_ctrl.get_digital_new_press(h_ctrl_digital::E_CONTROLLER_DIGITAL_RIGHT))  // Scroll right.
            { if (current_sel < 2) {++current_sel;} }
        else if (h_obj_ctrl.get_digital_new_press(h_ctrl_digital::E_CONTROLLER_DIGITAL_A))      // Select.
        { 
            h_obj_ctrl.rumble("...");   // Rumble to let you know you selected.
            break;                      // Exit the infinite loop.
        }

        pros::delay(10);    // Delay b/c the LCD can't refresh faster than this.
    }
    
    clear_screen();
}

// Disabled state callback.
void disabled()
{
    // Unallocate memory from heap memory after autonomous is complete.
    delete a_obj_pid;
    delete a_obj_bad_move;
    // Set the pointers to nullptr so we don't access illegal memory addresses.
    a_obj_pid = nullptr;
    a_obj_bad_move = nullptr;
}

// Competition initialization callback.
void competition_initialize()
{

}

// Main initialization callback.
void initialize()
{
    // Initialize LLEMU.
    pros::lcd::initialize();

    // Create all the control objects.
    h_obj_intake = new h_Intake{h_Intake_Ports{17, 7}};
    h_obj_conveyor = new h_Conveyor{h_Conveyor_Ports{8, 15}};
    h_obj_chassis = new h_Chassis{h_Drive_Ports{19, 20, 9, 10}};
    h_obj_sensors = new h_Sensors{h_Smart_Sen_Ports{16, 6}, h_Analog_Sen_Ports{5, 1, 3}};

    h_obj_sensors->initialize();     // Initialize the sensor object.
    h_obj_sensors->add_sig(h_obj_red_sig, h_sVision_IDs::RED_ID)     // Add red Vision sig.
                 .add_sig(h_obj_blu_sig, h_sVision_IDs::BLUE_ID);   // Add blue Vision sig.

    pros::lcd::print(0, "everything initialized.");
    pros::delay(500);
    clear_screen(); // Clear screen.

    selector_screen();  // Run selection screen.
}
