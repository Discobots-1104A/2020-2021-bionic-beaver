//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Hardware class declarations.

//! Prefix all objects here with "h_" except for child members.

#ifndef HARDWARE_HPP
#define HARDWARE_HPP

//* Headers
#include "api.h"    // PROS API header.


//* Constants


//* User-defined types

/// struct - drive Ports.
//! In order of: LF, LB, RF, RB.
struct h_Drive_Ports
{
    int pt_LF;  // Drive port, left front.
    int pt_LB;  // Drive port, left back.
    int pt_RF;  // Drive port, right font.
    int pt_RB;  // Drive port, right back.
};

/// struct - Conveyor ports.
//! In order of: bottom, top.
struct h_Conveyor_Ports
{
    int pt_CB;  // Conveyor port, bottom.
    int pt_CT;  // Conveyor port, top.
};

/// struct - Intake ports.
//! In order of: left, right.
struct h_Intake_Ports
{
    int pt_IL;  // Intake port, left.
    int pt_IR;  // Intake port, right.
};

/// struct - Smart sensor ports.
//! In order of: IMU, Vision
struct h_Smart_Sen_Ports
{
    int pt_IMU;
    int pt_Vision;
};

/// struct - Analog sensor ports.
//! Use only the top port number.
//! In order of: Left tracking wheel, right tracking wheel, middle tracking wheel.
struct h_Analog_Sen_Ports
{
    int pt_Enc_LT;
    int pt_Enc_LB;
    int pt_Enc_RT;
    int pt_Enc_RB;
    int pt_Enc_MT;
    int pt_Enc_MB;

    h_Analog_Sen_Ports(int LT, int RT, int MT);
};

#endif  // HARDWARE_HPP
