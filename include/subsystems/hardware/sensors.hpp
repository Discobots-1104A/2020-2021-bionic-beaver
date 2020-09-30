//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-29
//* Desc: Sensors class declarations.

//! Prefix all objects here with "h_" except for child members and namespaces.

#ifndef H_SENSORS_HPP
#define H_SENSORS_HPP

//* Headers
#include "api.h"

//* User-defined types

/// struct - Smart sensor ports.
//? In order of: IMU, Vision
struct h_Smart_Sen_Ports
{
    std::uint8_t pt_IMU;    // Smart sensor port, IMU.
    std::uint8_t pt_Vision; // Smart sensor port, Vision.
};

/// struct - Analog sensor ports. 
//! Use only the top port number. 
//? In order of: Left tracking wheel, right tracking wheel, middle tracking wheel. 
struct h_Analog_Sen_Ports
{
    std::uint8_t pt_Enc_LT; // Analog port, encoder left top.
    std::uint8_t pt_Enc_LB; // Analog port, encoder left bottom.
    std::uint8_t pt_Enc_RT; // Analog port, encoder right top.
    std::uint8_t pt_Enc_RB; // Analog port, encoder right bottom.
    std::uint8_t pt_Enc_MT; // Analog port, encoder middle top.
    std::uint8_t pt_Enc_MB; // Analog port, encoder middle bottom.

    h_Analog_Sen_Ports(std::uint8_t LT, std::uint8_t RT, std::uint8_t MT);
};

#endif  // H_SENSORS_HPP
