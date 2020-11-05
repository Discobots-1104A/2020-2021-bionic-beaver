//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Sensors class definitions

#include "main.h"


/// Converts ADI char to uint8_t.
/// \param adi_port ADI port in char.
/// \return Converted port to uint8_t
std::uint8_t operator"" _ADI(char adi_port)
{
    std::uint8_t return_;
    switch (adi_port)
    {
        case 'A':
            return_ = 1u; break;
        case 'B':
            return_ = 2u; break;
        case 'C':
            return_ = 3u; break;
        case 'D':
            return_ = 4u; break;
        case 'E':
            return_ = 5u; break;
        case 'F':
            return_ = 6u; break;
        case 'G':
            return_ = 7u; break;
        case 'H':
            return_ = 8u; break;
    }
    return return_;
}

/// Constructor for h_Sensors_ADI_Config
/// \param enc_left_top Top port of left ADI encoder.
/// \param enc_right_top Top port of right ADI encoder.
/// \param enc_mid_top Top port of middle ADI encoder.
/// \param enc_left_rev Direction of left ADI encoder.
/// \param enc_right_rev Direction of right ADI encoder.
/// \param enc_middle_rev Direction of middle ADI encoder.
h_Sensors_ADI_Config::h_Sensors_ADI_Config
(
    std::uint8_t enc_left_top, std::uint8_t enc_right_top, std::uint8_t enc_mid_top,
    bool enc_left_rev, bool enc_right_rev, bool enc_mid_rev
)   : m_adi_enc_lt{enc_left_top}, m_adi_enc_rt{enc_right_top}, m_adi_enc_mt{enc_mid_top},
      m_adi_enc_lb{++enc_left_top}, m_adi_enc_rb{++enc_right_top}, m_adi_enc_mb{++enc_mid_top},
      m_adi_enc_l_reversed{enc_left_rev}, m_adi_enc_r_reversed{enc_right_rev}, m_adi_enc_m_reversed{enc_mid_rev}
{}

h_Sensors::h_Sensors
(
    h_Sensors_Scales        scales,
    h_Sensors_Smart_Ports   smart_ports,
    h_Sensors_ADI_Config    adi_ports
)   : m_s_vision{smart_ports.m_imu}, m_s_imu{smart_ports.m_imu},
      m_adi_enc_l{pros::c::adi_encoder_init(adi_ports.m_adi_enc_lt, adi_ports.m_adi_enc_lb, adi_ports.m_adi_enc_l_reversed)},
      m_adi_enc_r{pros::c::adi_encoder_init(adi_ports.m_adi_enc_rt, adi_ports.m_adi_enc_rb, adi_ports.m_adi_enc_r_reversed)},
      m_adi_enc_m{pros::c::adi_encoder_init(adi_ports.m_adi_enc_mt, adi_ports.m_adi_enc_mb, adi_ports.m_adi_enc_m_reversed)},
      m_vision_sensor_height{scales.m_vision_scales.m_vision_sensor_angle}, m_vision_sensor_angle{scales.m_vision_scales.m_vision_sensor_angle},
      m_tracking_wheel_wheelbase{scales.m_tracking_wheel_scales.m_tracking_wheel_wheelbase},
      m_side_tracking_wheel_radius{scales.m_tracking_wheel_scales.m_side_tracking_wheel_radius},
      m_middle_tracking_wheel_radius{scales.m_tracking_wheel_scales.m_middle_tracking_wheel_radius}
{}
