//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Initialization code.

#include "main.h"


void initialize() 
{
    pros::lcd::initialize();
    pros::delay(1000);
    
    h_obj_chassis = new h_Skid_Steer_Chassis{
        h_Chassis_Port_Numbers{19, 20, -9, -10},
        h_Chassis_Scales{{17.5, 15.56}, {4.0, 12.5}, {200, 257, 1.25}}
    };
    h_obj_conveyor = new h_Conveyor{
        h_Conveyor_Port_Numbers{8, -15},
        h_Conveyor_Scales{600, 1200}
    };
    h_obj_intake = new h_Intake{
        h_Intake_Port_Numbers{17, -7},
        h_Intake_Scales{600}
    };
    h_obj_sensors = new h_Sensors{
        h_Sensors_Scales{{0.0, 0.0, pros::E_VISION_ZERO_TOPLEFT}, {12.0, 6.25, 6.5, 3.25}},
        h_Sensors_Smart_Ports{6, 16},
        h_Sensors_ADI_Config{'E'_ADI, 'A'_ADI, 'C'_ADI, true, false, false}
    };
    c_obj_odom = new c_Odometry{
        c_obj_default_starting_positions,
        c_obj_goal_coords,
        c_obj_live_comp_setup_coords,
        c_obj_skills_setup_coords,
        h_obj_sensors, h_obj_chassis, c_Robot_Starting_Pos_Side::RED
    };
}

void disabled() 
{

}

void competition_initialize() 
{

}
