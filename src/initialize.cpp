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
    for (auto i{0}; i < k_Hardware::h_llemu_lines; ++i)
        pros::lcd::clear_line(i);
}

// Selects autos and ball sorting colour
void selector_screen()
{
    int current_sel {0};
    while (true)
    {
        // Printing text on screen
        switch (current_sel)
        {
        case 0:
            pros::lcd::print(0, "sort col: red  ");
            h_sorted_ball_id = h_sVision_IDs::RED_ID;
            break;
        case 1:
            pros::lcd::print(0, "sort col: blue ");
            h_sorted_ball_id = h_sVision_IDs::BLUE_ID;
            break;
        case 2:
            pros::lcd::print(0, "sort col: skills");
            h_sorted_ball_id = h_sVision_IDs::BLUE_ID;
            break;
        }

        if (h_obj_ctrl.get_digital_new_press(h_ctrl_digital::E_CONTROLLER_DIGITAL_LEFT))
            { if (current_sel > 0) {--current_sel;} }
        else if (h_obj_ctrl.get_digital_new_press(h_ctrl_digital::E_CONTROLLER_DIGITAL_RIGHT))
            { if (current_sel < 2) {++current_sel;} }
        else if (h_obj_ctrl.get_digital_new_press(h_ctrl_digital::E_CONTROLLER_DIGITAL_A))
        { 
            h_obj_ctrl.rumble("...");
            clear_screen(); 
            break; 
        }

        pros::delay(10);
    }
}

// Disabled state callback.
void disabled()
{
    delete a_obj_pid;
    delete a_obj_bad_move;
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
    pros::lcd::initialize();

    h_obj_intake = new h_Intake{h_Intake_Ports{17, 7}};
    h_obj_conveyor = new h_Conveyor{h_Conveyor_Ports{8, 15}};
    h_obj_chassis = new h_Chassis{h_Drive_Ports{19, 20, 9, 10}};
    h_obj_sensors = new h_Sensors{h_Smart_Sen_Ports{16, 6}, h_Analog_Sen_Ports{5, 1, 3}};

    h_obj_sensors->initialize();     // Initialize the sensor object.
    h_obj_sensors->add_sig(h_obj_red_sig, h_sVision_IDs::RED_ID)     // Add red Vision sig.
                 .add_sig(h_obj_blu_sig, h_sVision_IDs::BLUE_ID);   // Add blue Vision sig.

    pros::lcd::print(0, "everything initialized.");
    pros::delay(500);
    clear_screen();

    selector_screen();  // Run selection screen.
}
