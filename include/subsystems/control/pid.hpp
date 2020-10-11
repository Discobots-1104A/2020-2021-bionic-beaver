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

/// enum - Sides for auto.
enum a_Sides
{
    LEFT,
    RIGHT
};

/// struct - Encoder ticks 
struct a_Ticks
{
    double var;
};

/// struct - Degrees
struct a_Degrees
{
    double var;
};

/// struct - PID constants. 
//? In order of: kP, kI, kD, k_Dt, k_min_intg, k_uncert. 
struct a_PID_Gains
{
    double gn_kP;
    double gn_kI;
    double gn_kD;
    double gn_k_Dt;
    double gn_k_min_intg;
    double gn_k_t_uncert;
    double gn_k_h_uncert;
};

/// class - PID.
/// Has all necessary objects and functions.
class a_PID
{
public:
    a_PID(const a_PID_Gains &gains);
    a_PID& set_gains(const a_PID_Gains &gains);
    a_PID& set_target(const a_Ticks &dist_target);
    a_PID& set_target(const a_Degrees &head_target);
    a_PID& reset();
    void drive();

private:
    double m_kP;
    double m_kI;
    double m_kD;
    double m_k_Dt;
    double m_k_min_intg;
    double m_k_t_uncert;
    double m_k_h_uncert;

    double m_targ_dist, m_targ_head;
    double m_targ_l, m_targ_r;
    double m_err_l, m_err_r;
    double m_lst_err_l, m_lst_err_r;
    double m_derv_l, m_derv_r;

    void calculate_str();
    void calculate_p_trn();
};

#endif  // A_PID_HPP
