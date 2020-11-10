//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Global variables

#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "main.h"


enum class g_Robot_Starting_Pos_Side
{
    RED,
    BLUE,
    SKILLS
};

extern h_Skid_Steer_Chassis *h_obj_chassis;
extern h_Conveyor           *h_obj_conveyor;
extern h_Intake             *h_obj_intake;
extern h_Sensors            *h_obj_sensors;
extern c_Odometry           *c_obj_odom;

extern const c_Robot_Starting_Positions         c_obj_default_starting_positions;
extern const c_All_Goal_Coords                  c_obj_goal_coords;
extern const c_Live_Comp_Setup_Startup_Coords   c_obj_live_comp_setup_coords;
extern const c_Skills_Setup_Startup_Coords      c_obj_skills_setup_coords;

#endif  // GLOBALS_HPP
