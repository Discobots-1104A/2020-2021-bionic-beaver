//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Hardware class definitions.


//* Headers

// Main header.
#include "main.h"


//* Definitions

/// struct - Analog sensor ports.
/// \param LT Top port of the left OSR.
/// \param RT Top port of the right OSR.
/// \param MT Top port of the middle OSR.
h_Analog_Sen_Ports::h_Analog_Sen_Ports(int LT, int RT, int MT)
    : pt_Enc_LT {LT}, pt_Enc_LB {++LT}, pt_Enc_RT {RT}, pt_Enc_RB {++RT} , pt_Enc_MT {MT} , pt_Enc_MB {++MT}
    {}
