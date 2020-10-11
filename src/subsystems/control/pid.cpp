//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-10-03
//* Desc: PID class definitons.

// TODO: Add async ability to the PID controller.
// TODO: Add smart turning deduction (currently takes long way to targets)

//* Headers
#include "main.h"   // Main header.


//* Private definitions

/// Calculation function for straight line movements.
void a_PID::calculate_str()
{
    std::uint32_t uint_m_k_Dt = static_cast<std::uint32_t>(m_k_Dt);

    while ((m_targ_dist - h_obj_sensors.get_enc(h_Encoder_IDs::AVG_SIDES)) > m_k_uncert)
    {
        int output_l, output_r;

        if (m_targ_dist)
        {
            m_err_l = m_targ_dist - h_obj_sensors.get_enc(h_Encoder_IDs::LEFT);
            m_err_r = m_targ_dist - h_obj_sensors.get_enc(h_Encoder_IDs::RIGHT);

            m_derv_l = (m_err_l - m_lst_err_l) / m_k_Dt;
            m_derv_r = (m_err_r - m_lst_err_r) / m_k_Dt;


            output_l = (m_err_l * m_kP) + (m_derv_l * m_kD);
            output_r = (m_err_r * m_kP) + (m_derv_r * m_kD);
            output_l = (std::abs(output_l) > 200) ? std::copysign(output_l, 200) : output_l;
            output_r = (std::abs(output_r) > 200) ? std::copysign(output_r, 200) : output_r;

            m_lst_err_l = m_err_l;
            m_lst_err_r = m_err_r;
        }

        h_obj_chassis.drive_vel(output_l, output_r);
        pros::delay(uint_m_k_Dt);
    }
}

//* Public definitions

/// class - PID controller. 
/// \param gains An a_PID_Gains struct with all gain values.
a_PID::a_PID(const a_PID_Gains &gains)
    : m_kP{gains.gn_kP}, m_kI{gains.gn_kI}, m_kD{gains.gn_kD}, m_k_Dt{gains.gn_k_Dt}, m_k_min_intg{gains.gn_k_min_intg}
    {}

/// Sets the gains of the PID controller.
/// \param gains An a_PID_Gains struct with all gain values.
a_PID& a_PID::set_gains(const a_PID_Gains &gains)
{
    m_kP = gains.gn_kP;
    m_kI = gains.gn_kI;
    m_kD = gains.gn_kD;
    m_k_Dt = gains.gn_k_Dt;
    m_k_min_intg = gains.gn_k_min_intg;
    m_k_uncert = gains.gn_k_uncert;
    return *this;
}

/// Sets the distance target of the PID controller.
/// \param dist_target Target distance in ticks.
a_PID& a_PID::set_target(const a_Ticks &dist_target)
{
    m_targ_dist = dist_target.var;
    return *this;
}

/// Sets the heading target of the PID controller.
/// \param head_target Target heading in degrees.
a_PID& a_PID::set_target(const a_Degrees &head_target)
{
    m_targ_head = head_target.var;
    return *this;
}

/// Resets all targets, errors, and calculated gains.
a_PID& a_PID::reset()
{
    m_targ_dist = 0.0;
    m_targ_head = 0.0;
    m_targ_l = 0.0;
    m_targ_r = 0.0;

    m_err_l = 0.0;
    m_err_r = 0.0;
    m_lst_err_l = 0.0;
    m_lst_err_r = 0.0;
    m_derv_l = 0.0;
    m_derv_r = 0.0;
    return *this;
}

/// Starts the PID controller with the supplied targets. 
/// Automatically deduces whether it should drive in a straight line, or 
/// do a point turn based on targets supplied.
void a_PID::drive()
{
    if (m_targ_dist)
    {
        calculate_str(); 
    }

    a_PID::reset();
}
