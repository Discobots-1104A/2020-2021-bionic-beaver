//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Operator control code.

#include "main.h"


//* Check deadzone
auto check_deadzone 
{[](int var){
    return (std::abs(var) > g_Constants::g_teleop_deadzone) ? var : 0;
}};

//* Chassis control task
void chassis_control()
{
    while (!(pros::competition::is_autonomous() || pros::competition::is_disabled()))
    {
        int pow  {check_deadzone(h_obj_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y))};
        int turn {check_deadzone(h_obj_controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X))};

        h_obj_chassis->move(pow + turn, pow - turn);

        pros::delay(10);
    }
}

void opcontrol() 
{
    c_obj_odom->start_odom(c_obj_default_starting_positions);

    pros::Task t_chassis {chassis_control};
}
