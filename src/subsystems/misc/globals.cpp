//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Global variables

#include "subsystems/misc/globals.hpp"


h_Skid_Steer_Chassis    *h_obj_chassis;
h_Conveyor              *h_obj_conveyor;
h_Intake                *h_obj_intake;
h_Sensors               *h_obj_sensors;
c_Odometry              *c_obj_odom;

const c_Robot_Starting_Positions c_obj_default_starting_positions{
    {4.416, 35.121, 90.0},
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 0.0}
};

const c_All_Goal_Coords c_obj_goal_coords{
    {5.8, 134.9, 315.0},
    {70.3, 134.9, 0.0},
    {134.9, 134.9, 45.0},
    {5.8, 70.3, 270.0},
    {70.3, 70.3, 0.0},
    {134.9, 70.3, 90.0},
    {5.8, 5.8, 225.0},
    {70.3, 5.8, 180.0},
    {134.9, 5.8, 135.0}
};

const c_Live_Comp_Setup_Startup_Coords c_obj_live_comp_setup_coords{
    {12.0, 138.5, h_Sensors_Vision_Signatures::RED_ID},
    {70.3, 105.7, h_Sensors_Vision_Signatures::RED_ID},
    {138.5, 138.5, h_Sensors_Vision_Signatures::BLUE_ID},
    {70.3, 79.1, h_Sensors_Vision_Signatures::RED_ID},
    {61.5, 70.3, h_Sensors_Vision_Signatures::BLUE_ID},
    {79.1, 70.3, h_Sensors_Vision_Signatures::RED_ID},
    {70.3, 61.5, h_Sensors_Vision_Signatures::BLUE_ID},
    {70.3, 35.0, h_Sensors_Vision_Signatures::BLUE_ID},
    {12.0, 12.0, h_Sensors_Vision_Signatures::RED_ID},
    {138.5, 12.0, h_Sensors_Vision_Signatures::BLUE_ID}
};

const c_Skills_Setup_Startup_Coords c_obj_skills_setup_coords{
    {35.123, 140.5, h_Sensors_Vision_Signatures::RED_ID},
    {105.365, 140.5, h_Sensors_Vision_Signatures::RED_ID},
    {70.25, 117.084, h_Sensors_Vision_Signatures::RED_ID},
    {23.416, 105.377, h_Sensors_Vision_Signatures::RED_ID},
    {117.084, 105.377, h_Sensors_Vision_Signatures::RED_ID},
    {70.25, 93.67, h_Sensors_Vision_Signatures::RED_ID},
    {46.83, 70.25, h_Sensors_Vision_Signatures::RED_ID},
    {93.67, 70.25, h_Sensors_Vision_Signatures::RED_ID},
    {70.25, 46.83, h_Sensors_Vision_Signatures::RED_ID},
    {23.416, 35.123, h_Sensors_Vision_Signatures::RED_ID},
    {117.084, 35.123, h_Sensors_Vision_Signatures::RED_ID},
    {70.25, 23.416, h_Sensors_Vision_Signatures::RED_ID},
    {35.123, 3.15, h_Sensors_Vision_Signatures::RED_ID},
    {105.365, 3.15, h_Sensors_Vision_Signatures::RED_ID}
};
