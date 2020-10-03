//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Main initialization code.


//* Headers
#include "main.h"   // Main header.


//* Functions

// Disabled state callback.
void disabled()
{

}

// Competition initialization callback.
void competition_initialize()
{

}

// Main initialization callback.
void initialize()
{
    h_obj_sensors.initialize();     // Initialize the sensor object.
    h_obj_sensors.add_sig(h_obj_red_sig, h_sVision_IDs::RED_ID)     // Add red Vision sig.
                 .add_sig(h_obj_blu_sig, h_sVision_IDs::BLUE_ID);   // Add blue Vision sig.

    h_obj_chassis.reset_enc();      // Reset chassis encoder values.
}
