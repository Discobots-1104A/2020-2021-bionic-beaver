//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-10-03
//* Desc: PID class definitons.


//* Headers
#include "main.h"   // Main header.


//* Private definitions

std::tuple<int, int> a_PID::calculate()
{
    m_error_l = m_target - h_obj_sensors.get_enc(h_Encoder_IDs::LEFT);
    m_error_r = m_target - h_obj_sensors.get_enc(h_Encoder_IDs::LEFT);

    m_derivative_l = (m_error_l - m_last_error_l) / m_k_Dt;
    m_derivative_r = (m_error_r - m_last_error_r) / m_k_Dt;


    m_output_l = (m_error_l * m_kP) + (m_derivative_l * m_kD);
    m_output_r = (m_error_r * m_kP) + (m_derivative_r * m_kD);
    if (std::abs(m_output_l) > 200) m_output_l = std::copysign(m_output_l, 200);
    if (std::abs(m_output_r) > 200) m_output_r = std::copysign(m_output_r, 200);

    m_last_error_l = m_error_l;
    m_last_error_r = m_error_r;
    
    return std::make_tuple(m_output_l, m_output_r);
}

//* Public definitions

a_PID::a_PID(const a_PID_Gains &gains)
    : m_kP{gains.gn_kP}, m_kI{gains.gn_kI}, m_kD{gains.gn_kD}, m_k_Dt{gains.gn_k_Dt}, m_k_min_intg{gains.gn_k_min_intg}
    {}

a_PID& a_PID::set_target(const a_Enc_Ticks &target)
{
    m_target = target.var;
    return *this;
}

void a_PID::reset()
{
    m_target = 0;
    m_error_l = 0;
    m_error_r = 0;
    m_last_error_l = 0;
    m_last_error_r = 0;
    m_derivative_l = 0;
    m_derivative_r = 0;
    m_output_l = 0;
    m_output_r = 0;
}

void a_PID::drive()
{
    while ((m_target - h_obj_sensors.get_enc(h_Encoder_IDs::AVG_SIDES)) > 5)
    {
        auto output {calculate()};
        h_obj_chassis.drive_vel(std::get<0>(output), std::get<1>(output));
        pros::delay(static_cast<std::uint32_t>(m_k_Dt));
    }
    a_PID::reset();
}