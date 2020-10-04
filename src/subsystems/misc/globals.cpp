//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Hardware declarations.

//! Prefix all objects here with "h_" except for child members and namespaces.

//*Headers
#include "main.h"

//* External objects

h_Intake h_obj_intake {h_Intake_Ports{17, 7}};
h_Conveyor h_obj_conveyor {h_Conveyor_Ports{8, 15}};
h_Chassis h_obj_chassis {h_Drive_Ports{19, 20, 9, 10}};
h_Sensors h_obj_sensors {h_Smart_Sen_Ports{16, 6}, h_Analog_Sen_Ports{5, 1, 3}};

pros::vision_signature_s_t h_obj_red_sig 
{
    pros::Vision::signature_from_utility
    (
        static_cast<std::int32_t>(h_sVision_IDs::RED_ID),
        4229, 8837, 6533, -353, 1073, 3360, 1.5, 0
    )
};

pros::vision_signature_s_t h_obj_blu_sig 
{
    pros::Vision::signature_from_utility
    (
        static_cast<std::int32_t>(h_sVision_IDs::BLUE_ID),
        -2993, -1993, -2494, 9025, 13265, 11146, 1.5, 0
    )
};

pros::Controller h_obj_ctrl {pros::controller_id_e_t::E_CONTROLLER_MASTER};

h_sVision_IDs h_sorted_ball_id;
