//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-10-03
//* Desc: PID class definitons.

// TODO: Add async ability to the PID controller.

//* Headers
#include "main.h"   // Main header.


//* Private definitions

/// Calculation function for straight line movements.
void a_PID::calculate_str()
{
    // Explicitly convert m_k_Dt for use in pros::delay() later.
    std::uint32_t uint_m_k_Dt = static_cast<std::uint32_t>(m_k_Dt);

    // Output for left and right sides.
    int output_l, output_r;

    // Loop as long as the chassis has not reached its target.
    while (std::fabs(m_targ_dist - static_cast<double>(h_obj_sensors->get_enc(h_Encoder_IDs::AVG_SIDES))) > m_k_t_uncert)
    {
        // Calculate errors.
        m_err_l = m_targ_l - h_obj_sensors->get_enc(h_Encoder_IDs::LEFT);
        m_err_r = m_targ_r - h_obj_sensors->get_enc(h_Encoder_IDs::RIGHT);

        // Calculate derivatives.
        m_derv_l = (m_err_l - m_lst_err_l) / m_k_Dt;
        m_derv_r = (m_err_r - m_lst_err_r) / m_k_Dt;

        // Explicitely convert the values to integers to write to the motors.
        output_l = static_cast<int>(std::round((m_err_l * m_kP) + (m_derv_l * m_kD)));
        output_r = static_cast<int>(std::round((m_err_r * m_kP) + (m_derv_r * m_kD)));

        // Check whether the values are too high or too low to be used (left side).
        if (std::abs(output_l) > k_Hardware::h_max_chassis_vel)
            output_l = std::copysign(output_l, k_Hardware::h_max_chassis_vel);
        else if (std::abs(output_l) < k_Hardware::h_min_chassis_vel)
            output_l = std::copysign(output_l, k_Hardware::h_min_chassis_vel);
        // Check whether the values are too high or too low to be used (right side).
        if (std::abs(output_r) > k_Hardware::h_max_chassis_vel)
            output_r = std::copysign(output_r, k_Hardware::h_max_chassis_vel);
        else if (std::abs(output_r) < k_Hardware::h_min_chassis_vel)
            output_r = std::copysign(output_r, k_Hardware::h_min_chassis_vel);

        // Set previous errors.
        m_lst_err_l = m_err_l;
        m_lst_err_r = m_err_r;

        // Set output power to the drive.
        h_obj_chassis->drive_vel(output_l, output_r);

        // Delay because the OCRs cannot record values faster than this.
        pros::delay(uint_m_k_Dt);
    }
}


/// Calculation function for point turn movements.
void a_PID::calculate_p_trn()
{
    std::uint32_t uint_m_k_Dt = static_cast<std::uint32_t>(m_k_Dt);

    int output_l, output_r;
    
    while (std::fabs(m_targ_head - h_obj_sensors->get_heading()) > m_k_h_uncert)
    {
        // Calculate the shortest angle towards the target from current heading.
        double diff { fmod( (m_targ_head - h_obj_sensors->get_heading() + 180.0), 360.0) - 180 };
        double theta { ( (diff < -180) ? diff + 360 : diff ) };

        // Set errors.
        m_err_l = theta;
        m_err_r = -theta;

        // Calculate derivatives.
        m_derv_l = (m_err_l - m_lst_err_l) / m_k_Dt;
        m_derv_r = (m_err_r - m_lst_err_r) / m_k_Dt;

        // Explicitely convert the values to integers to write to the motors.
        output_l = static_cast<int>(std::round((m_err_l * m_kP) + (m_derv_l * m_kD)));
        output_r = static_cast<int>(std::round((m_err_r * m_kP) + (m_derv_r * m_kD)));

        // Check whether the values are too high or too low to be used (left side).
        if (std::abs(output_l) > k_Hardware::h_max_chassis_vel)
            output_l = std::copysign(output_l, k_Hardware::h_max_chassis_vel);
        else if (std::abs(output_l) < k_Hardware::h_min_chassis_vel)
            output_l = std::copysign(output_l, k_Hardware::h_min_chassis_vel);
        // Check whether the values are too high or too low to be used (right side).
        if (std::abs(output_r) > k_Hardware::h_max_chassis_vel)
            output_r = std::copysign(output_r, k_Hardware::h_max_chassis_vel);
        else if (std::abs(output_r) < k_Hardware::h_min_chassis_vel)
            output_r = std::copysign(output_r, k_Hardware::h_min_chassis_vel);

        // Set previous errors.
        m_lst_err_l = m_err_l;
        m_lst_err_r = m_err_r;

        // Set output power to the drive.
        h_obj_chassis->drive_vel(output_l, output_r);

        // Delay because the OCRs cannot record values faster than this.
        pros::delay(uint_m_k_Dt); 
    }
}

//* Public definitions

/// class - PID controller. 
/// \param gains An a_PID_Gains struct with all gain values.
a_PID::a_PID(const a_PID_Gains &gains)
    : m_kP{gains.gn_kP}, m_kI{gains.gn_kI}, m_kD{gains.gn_kD}, 
      m_k_Dt{gains.gn_k_Dt}, m_k_min_intg{gains.gn_k_min_intg},
      m_k_t_uncert{gains.gn_k_t_uncert}, m_k_h_uncert{gains.gn_k_h_uncert}
    {}

/// Resets all targets, errors, calculated gains, and sensor readings.
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

    h_obj_sensors->reset();
    
    return *this;
}

/// Sets the gains of the PID controller.
/// \param gains An a_PID_Gains struct with all gain values.
a_PID& a_PID::set_gains(const a_PID_Gains &gains)
{
    m_kP = gains.gn_kP;
    m_kI = gains.gn_kI;
    m_kD = gains.gn_kD;
    m_k_Dt = gains.gn_k_Dt;
    m_k_min_intg = gains.gn_k_min_intg;
    m_k_t_uncert = gains.gn_k_t_uncert;
    m_k_h_uncert = gains.gn_k_h_uncert;
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

/// Starts the PID controller with the supplied targets. 
/// Automatically deduces whether it should drive in a straight line, or 
/// do a point turn based on targets supplied.
void a_PID::drive()
{
    // If we detect a distance target...
    if (m_targ_dist)
    {
        // Set the targets.
        m_targ_l = m_targ_dist;
        m_targ_r = m_targ_dist;

        // Start distance calculation.
        calculate_str();
    }
    // Otherwise if it's a heading target...
    else if (m_targ_head)
    {
        // Start heading calculation
        calculate_p_trn();
    }

    // Stop the motors.
    h_obj_chassis->drive_vel();

    // Reset all values.
    reset();
}
