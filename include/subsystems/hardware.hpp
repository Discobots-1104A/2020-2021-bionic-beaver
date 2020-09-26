//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-26
//* Desc: Hardware class declarations.


//* Headers
#include "api.h"    // PROS API header.


//* Declarations

namespace k_Hardware
{
    //* Constants


    //* User-defined types

    /// struct - drive Ports.
    //! In order of: LF, LB, RF, RB.
    struct Drive_Ports
    {
        int pt_LF;  // Drive port, left front.
        int pt_LB;  // Drive port, left back.
        int pt_RF;  // Drive port, right font.
        int pt_RB;  // Drive port, right back.
    };

    /// struct - Conveyor ports.
    //! In order of: bottom, top.
    struct Conveyor_Ports
    {
        int pt_CB;  // Conveyor port, bottom.
        int pt_CT;  // Conveyor port, top.
    };

    /// struct - Intake ports.
    //! In order of: left, right.
    struct Intake_Ports
    {
        int pt_IL;  // Intake port, left.
        int pt_IR;  // Intake port, right.
    };

}
