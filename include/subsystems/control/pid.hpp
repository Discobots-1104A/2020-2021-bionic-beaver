//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-10-03
//* Desc: PID class declarations.

//! Prefix all objects here with "a_" except for child members and namespaces.

#ifndef A_PID_HPP
#define A_PID_HPP

//* Headers
#include "api.h"

//* User-defined types

/// struct - Encoder ticks 
struct a_Enc_Ticks
{
    double var;
};

/// struct - Degrees
struct a_Degrees
{
    double var;
};

/// struct - PID constants. 
//? In order of: kP, kI, kD, k_Dt, k_min_intg. 
struct a_PID_Gains
{
    double gn_kP;
    double gn_kI;
    double gn_kD;
    double gn_k_Dt;
    double gn_k_min_intg;
};

/// class - PID.
/// Has all necessary objects and functions.
class a_PID
{
public:
    a_PID(const a_PID_Gains &gains);
    a_PID& set_target(const a_Enc_Ticks &target);
    void reset();
    void drive();

private:
    double m_kP;
    double m_kI;
    double m_kD;
    double m_k_Dt;
    double m_k_min_intg;

    double m_target;
    double m_error_l;
    double m_error_r;
    double m_last_error_l;
    double m_last_error_r;
    double m_derivative_l;
    double m_derivative_r;
    double m_output_l;
    double m_output_r;

    std::tuple<int, int> calculate();

};

#endif  // A_PID_HPP
