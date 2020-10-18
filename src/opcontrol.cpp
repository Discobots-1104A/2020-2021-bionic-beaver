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

/// Deadzone function. Checks to ensure the joystick values are within a given range.
/// \param var Joystick value.
/// \return The value again, or zero if it's less than the deadzone range.
int check_deadzone(int var)
{
    return (std::abs(var) > k_Hardware::h_deadzone ? var : 0);
}

/// Ball sorting function. Determines whether it should reverse the top roller or 
/// not to eject a ball.
/// \param ball The ball of the given sorted signature.
/// \param top_pow The default power of the top roller.
/// \return The top value or the reversing value depending on the size of the object.
int ball_sort(pros::vision_object_s_t &ball, int top_pow)
{
    return ((ball.width > 50) ? k_Hardware::h_rev_top : top_pow);
}

// Driver control.
void drive_control()
{
    while (!pros::competition::is_autonomous())
    {
        // Get power and turn voltages.
        int pow {check_deadzone(h_obj_ctrl.get_analog(h_ctrl_analog::E_CONTROLLER_ANALOG_RIGHT_Y))},
            trn {check_deadzone(h_obj_ctrl.get_analog(h_ctrl_analog::E_CONTROLLER_ANALOG_RIGHT_X))};

        // Assign to drive.
        h_obj_chassis->drive_vol(pow + trn, pow - trn);

        // Delay to not hog resources.
        pros::delay(10);
    }
}

// Conveyor and intake control.
void conveyor_intake_control()
{
    while (!pros::competition::is_autonomous())
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
            is_auto_sort = !is_auto_sort;   // Flip is_auto_sort
            h_obj_ctrl.rumble(is_auto_sort ? "..." : "---");    // 3 short rumbles for on, 3 long for off
        }
        // We just stop the motors otherwise.
        else
        {
            h_obj_intake->set_vel();
            h_obj_intake->reset_enc();
            h_obj_conveyor->set_vel();
        }
        
        // Delay to not hog resources.
        pros::delay(10);
    }
}

// Main operator control callback.
void opcontrol()
{
    // Tasks are created to allow chassis control, conveyor & intake control, and debug 
    // to run concurrently.

    pros::Task chassis_task {drive_control, "tChassis"};
    pros::Task conveyor_intake_task {conveyor_intake_control, "tConveyorIntake"};
}

//* Macros

// Indexing.
void macro_indexing()
{
    // Get a ball object of the given signature.
    pros::vision_object_s_t ball {h_obj_sensors->get_obj_sig(0, h_sorted_ball_id)};

    // Set the velocity of the conveyor, using the ball sort function (if it is on).
    h_obj_conveyor->set_vel(
        (is_auto_sort ? ball_sort(ball, 0) : 600),
        600);
    // Set the velocity of the intakes.
    h_obj_intake->set_vel(600);
}

// Cycling.
void macro_cycling()
{
    // Get a ball object of the given signature.
    pros::vision_object_s_t ball {h_obj_sensors->get_obj_sig(0, h_sorted_ball_id)};

    // Set the velocity of the conveyor, using the ball sort function (if it is on).
    h_obj_conveyor->set_vel(
        (is_auto_sort ? ball_sort(ball, 600) : 600),
        600);
    // Set the velocity of the intakes.
    h_obj_intake->set_vel(600);
}

// Shooting.
void macro_shooting()
{
    // Set the velocity of the conveyor.
    h_obj_conveyor->set_vel(600);
    // Run the intakes for a short period of time.
    h_obj_intake->set_abs(750, 600);
}

// Run intakes.
void macro_intake()
{
    // Set the velocity of the intakes.
    h_obj_intake->set_vel(600);
}

// Emergency macro 1.
void macro_outtake()
{
    // Set the velocity of the conveyor.
    h_obj_conveyor->set_vel(-600);
    // Set the velocity of the intakes.
    h_obj_intake->set_vel(-600);
}

// Emergency macro 2.
void macro_conveyor_rev()
{
    // Set the velocity of the conveyor.
    h_obj_conveyor->set_vel(-600);
}
