//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-10-03
//* Desc: PID class definitons.


//* Headers
#include "main.h"   // Main header.


//* Private definitions

/// Main function that performs all calculations necessary with the targets and gains 
/// supplied beforehand. Automatically deduces whether to calculate for a straight line 
/// or for a point turn.
/// \return A 2-integer tuple that carries the left and right side velocties.
std::tuple<int, int> a_PID::calculate()
{
    int m_output_l, m_output_r;

    if (std::get<a_Targets::DISTANCE>(m_targets))
    {
        std::get<a_Sides::LEFT>(m_errors)  = std::get<a_Targets::DISTANCE>(m_targets) - h_obj_sensors.get_enc(h_Encoder_IDs::LEFT);
        std::get<a_Sides::RIGHT>(m_errors) = std::get<a_Targets::DISTANCE>(m_targets) - h_obj_sensors.get_enc(h_Encoder_IDs::LEFT);

        std::get<a_Sides::LEFT>(m_derivatives)  = (std::get<a_Sides::LEFT>(m_errors) - \
        std::get<a_Sides::LEFT>(m_last_errors))  / m_k_Dt;
        std::get<a_Sides::RIGHT>(m_derivatives) = (std::get<a_Sides::RIGHT>(m_errors)- \
        std::get<a_Sides::RIGHT>(m_last_errors)) / m_k_Dt;


        m_output_l = (std::get<a_Sides::LEFT>(m_errors)  * m_kP) + (std::get<a_Sides::LEFT>(m_derivatives)  * m_kD);
        m_output_r = (std::get<a_Sides::RIGHT>(m_errors) * m_kP) + (std::get<a_Sides::RIGHT>(m_derivatives) * m_kD);
        if (std::abs(m_output_l) > 200) m_output_l = std::copysign(m_output_l, 200);
        if (std::abs(m_output_r) > 200) m_output_r = std::copysign(m_output_r, 200);

        std::get<a_Sides::LEFT>(m_last_errors)  = std::get<a_Sides::LEFT>(m_errors);
        std::get<a_Sides::RIGHT>(m_last_errors) = std::get<a_Sides::RIGHT>(m_errors);
    }
    else if (std::get<a_Targets::HEADING>(m_targets))
    {
        std::get<a_Sides::LEFT>(m_errors) = std::get<a_Targets::HEADING>(m_targets) - h_obj_sensors.get_heading();

        std::get<a_Sides::LEFT>(m_derivatives)  = (std::get<a_Sides::LEFT>(m_errors) - \
        std::get<a_Sides::LEFT>(m_last_errors))  / m_k_Dt;

        m_output_l = (std::get<a_Sides::LEFT>(m_errors)  * m_kP) + (std::get<a_Sides::LEFT>(m_derivatives)  * m_kD);
        m_output_r = -((std::get<a_Sides::RIGHT>(m_errors) * m_kP) + (std::get<a_Sides::RIGHT>(m_derivatives) * m_kD));
        if (std::abs(m_output_l) > 200) m_output_l = std::copysign(m_output_l, 200);
        if (std::abs(m_output_r) > 200) m_output_r = std::copysign(m_output_r, 200);

        std::get<a_Sides::LEFT>(m_last_errors)  = std::get<a_Sides::LEFT>(m_errors);
    }
    return std::make_tuple(m_output_l, m_output_r);
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
}

/// Sets the targets of the PID controller.
/// \param dist_target Target distance in ticks.
/// \param head_target Target distance in degrees.
a_PID& a_PID::set_target(const a_Ticks &dist_target, const a_Degrees &head_target)
{
    m_targets = std::make_tuple(dist_target.var, head_target.var);
    return *this;
}

/// Resets all targets, errors, and calculated gains.
a_PID& a_PID::reset()
{
    m_targets = std::make_tuple(0, 0);
    m_errors = std::make_tuple(0, 0);
    m_last_errors = std::make_tuple(0, 0);
    m_derivatives = std::make_tuple(0, 0);
    return *this;
}

/// Starts the PID controller with the supplied targets. 
/// Automatically deduces whether it should drive in a straight line, or 
/// do a point turn based on targets supplied.
void a_PID::drive()
{
    if (std::get<a_Targets::DISTANCE>(m_targets))
    {
        while ((std::get<a_Targets::DISTANCE>(m_targets) - h_obj_sensors.get_enc(h_Encoder_IDs::AVG_SIDES)) > 5)
        {
            auto output {calculate()};
            h_obj_chassis.drive_vel(std::get<LEFT>(output), std::get<RIGHT>(output));
            pros::delay(static_cast<std::uint32_t>(m_k_Dt));
        }
    }
    else if (std::get<a_Targets::HEADING>(m_targets))
    {
        while ((std::get<a_Targets::HEADING>(m_targets) - h_obj_sensors.get_heading()) > 0.25)
        {
            auto output {calculate()};
            h_obj_chassis.drive_vel(std::get<LEFT>(output), std::get<RIGHT>(output));
            pros::delay(static_cast<std::uint32_t>(m_k_Dt));
        }
    }
    a_PID::reset();
}