//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Main operator control code.


//* Headers
#include "main.h"   // Main header.


//* Local "global" variables.
bool is_auto_sort {true};

//* Macro forward declarations
void macro_indexing();      // Indexing.
void macro_cycling();       // Cycling.
void macro_shooting();      // Shooting.
void macro_intake();        // Run intakes.
void macro_outtake();       // Emergency macro 1.
void macro_conveyor_rev();  // Emergecy macro 2.

//* Functions

// Deadzone function
int check_deadzone(int var)
{
    return (std::abs(var) > 10 ? var : 0);
}

// Ball sorting for later
int ball_sort(pros::vision_object_s_t &ball, int top_pow)
{
    return ((ball.width > 50) ? -600 : top_pow);
}

// Driver control
void drive_control()
{
    while (true)
    {
        // Get power and turn voltages.
        int pow {check_deadzone(h_obj_ctrl.get_analog(h_ctrl_analog::E_CONTROLLER_ANALOG_RIGHT_Y))},
            trn {check_deadzone(h_obj_ctrl.get_analog(h_ctrl_analog::E_CONTROLLER_ANALOG_RIGHT_X))};

        // Assign to drive.
        h_obj_chassis->drive_vol(pow + trn, pow - trn);

        // Delay to not hog resources.
        pros::delay(5);
    }
}

// Conveyor and intake control
void conveyor_intake_control()
{
    while (true)
    {
        // Big elif block to determine which buttons were pressed.
        // Links corrosponding functions with the button.
        if (h_obj_ctrl.get_digital(h_ctrl_digital::E_CONTROLLER_DIGITAL_R1))    // Indexing, R1
            macro_indexing();
        else if (h_obj_ctrl.get_digital(h_ctrl_digital::E_CONTROLLER_DIGITAL_R2))   // Cycling, R2
            macro_cycling();
        else if (h_obj_ctrl.get_digital(h_ctrl_digital::E_CONTROLLER_DIGITAL_L1))   // Shooting, L1
            macro_shooting();
        else if (h_obj_ctrl.get_digital(h_ctrl_digital::E_CONTROLLER_DIGITAL_L2))   // Run intakes, L2
            macro_intake();
        else if (h_obj_ctrl.get_digital(h_ctrl_digital::E_CONTROLLER_DIGITAL_UP))   // Emergency macro 1, Up
            macro_outtake();
        else if (h_obj_ctrl.get_digital(h_ctrl_digital::E_CONTROLLER_DIGITAL_DOWN)) // Emergency macro 2, Down
            macro_conveyor_rev();
        else if (h_obj_ctrl.get_digital_new_press(h_ctrl_digital::E_CONTROLLER_DIGITAL_RIGHT))  // Toggle sorting, Right
        {
            is_auto_sort = !is_auto_sort;
            h_obj_ctrl.rumble(is_auto_sort ? "..." : "---");
        }
        // We just stop the motors otherwise.
        else
        {
            h_obj_intake->set_vel();
            h_obj_intake->reset_enc();
            h_obj_conveyor->set_vel();
        }
        
        // Delay to not hog resources.
        pros::delay(5);
    }
}

// Debugging functions
void debug()
{
    while (true)
    {
        pros::lcd::print(0, "heading: %f", h_obj_sensors->get_heading());
        pros::lcd::print(1, "tr left: %d", h_obj_sensors->get_enc(h_Encoder_IDs::LEFT));
        pros::lcd::print(2, "tr right: %d", h_obj_sensors->get_enc(h_Encoder_IDs::RIGHT));
        pros::delay(10);
    }
}

// Main operator control callback.
void opcontrol()
{
    pros::Task chassis_task {drive_control, "tChassis"};
    pros::Task conveyor_intake_task {conveyor_intake_control, "tConveyorIntake"};
    pros::Task debug_task {debug, "tDebug"};
}

//* Macros

// Indexing.
void macro_indexing()
{
    pros::vision_object_s_t ball {h_obj_sensors->get_obj_sig(0, h_sorted_ball_id)};

    h_obj_conveyor->set_vel(
        (is_auto_sort ? ball_sort(ball, 0) : 600),
        600);
    h_obj_intake->set_vel(600);
}

// Cycling.
void macro_cycling()
{
    pros::vision_object_s_t ball {h_obj_sensors->get_obj_sig(0, h_sorted_ball_id)};

    h_obj_conveyor->set_vel(
        (is_auto_sort ? ball_sort(ball, 600) : 600),
        600);
    h_obj_intake->set_vel(600);
}

// Shooting.
void macro_shooting()
{
    h_obj_conveyor->set_vel(600);
    h_obj_intake->set_abs(750, 600);
}

// Run intakes.
void macro_intake()
{
    h_obj_intake->set_vel(600);
}

// Emergency macro 1.
void macro_outtake()
{
    h_obj_conveyor->set_vel(-600);
    h_obj_intake->set_vel(-600);
}

// Emergency macro 2.
void macro_conveyor_rev()
{
    h_obj_conveyor->set_vel(-600);
}
