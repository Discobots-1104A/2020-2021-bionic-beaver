//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Sensors class definitions

#include "main.h"


//* Miscellaneous *//

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


//* Constructors and destructors *//

/// h_Sensors_ADI_Config constructor. Automatically assigned bottom ports based on top ports. 
/// IMPORTANT: does not check if top ports are odd numbered ports and will not throw errors if it is done.
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

/// Sensors constructor. No default parameters, all parameters must be specified. 
/// Interfaces with PROS C functions to configure and use sensors.
/// \param scales Sensors scales.
/// \param smart_ports Smart port numbers.
/// \param adi_ports ADI ports--you can use "_ADI" if you want to use 'char's over 'uint8_t's.
h_Sensors::h_Sensors
(
    const h_Sensors_Scales&         scales,
    const h_Sensors_Smart_Ports&    smart_ports,
    const h_Sensors_ADI_Config&     adi_ports
)   : m_s_vision{smart_ports.m_imu}, m_s_imu{smart_ports.m_imu},
      m_adi_enc_l{pros::c::adi_encoder_init(adi_ports.m_adi_enc_lt, adi_ports.m_adi_enc_lb, adi_ports.m_adi_enc_l_reversed)},
      m_adi_enc_r{pros::c::adi_encoder_init(adi_ports.m_adi_enc_rt, adi_ports.m_adi_enc_rb, adi_ports.m_adi_enc_r_reversed)},
      m_adi_enc_m{pros::c::adi_encoder_init(adi_ports.m_adi_enc_mt, adi_ports.m_adi_enc_mb, adi_ports.m_adi_enc_m_reversed)},
      m_vision_sensor_height{scales.m_vision_scales.m_vision_sensor_angle}, m_vision_sensor_angle{scales.m_vision_scales.m_vision_sensor_angle},
      m_vision_zero_point{scales.m_vision_scales.m_vision_zero_point},
      m_tracking_wheel_wheelbase{scales.m_tracking_wheel_scales.m_tracking_wheel_wheelbase},
      m_side_tracking_wheel_radius{scales.m_tracking_wheel_scales.m_side_tracking_wheel_radius},
      m_middle_tracking_wheel_radius{scales.m_tracking_wheel_scales.m_middle_tracking_wheel_radius}
{}


//* General methods *//

/// Initializes all the sensors. Takes a bit because of IMU callibration.
/// \return this* pointer for function chaining.
h_Sensors& h_Sensors::initialize(void)
{
    // Start IMU early
    pros::c::imu_reset(m_s_imu);

    // Vision
    pros::c::vision_set_wifi_mode(m_s_vision, 0);
    vision_set_zero_point(m_vision_zero_point);

    // Tracking wheels
    pros::c::adi_encoder_reset(m_adi_enc_l);
    pros::c::adi_encoder_reset(m_adi_enc_r);
    pros::c::adi_encoder_reset(m_adi_enc_m);

    do {pros::delay(5);} while (imu_get_status() & pros::c::E_IMU_STATUS_CALIBRATING);
}


//* Vision sensor *//

/// \return Height from center of Vision camera to floor in inches.
double h_Sensors::vision_get_sensor_height(void) {return m_vision_sensor_height;}

/// \return Angle from floor to center of Vision camera to principle axis.
double h_Sensors::vision_get_sensor_angle(void) {return m_vision_sensor_angle;}

/// Get Vision objects by signature.
/// \param size The size of object to look for.
/// \param sig_id The ID of the signature to use.
/// \return A vision_object_s_t object.
pros::vision_object_s_t h_Sensors::vision_get_by_sig(int size, h_Sensors_Vision_Signatures sig_id)
{
    pros::c::vision_get_by_sig(m_s_vision, size, static_cast<std::uint32_t>(sig_id));
}

/// Get Vision objects by size.
/// \param size The size of object to look for.
/// \return A vision_object_s_t object.
pros::vision_object_s_t h_Sensors::vision_get_by_size(int size)
{
    pros::c::vision_get_by_size(m_s_vision, size);
}

/// \return The zero-point mode of the Vision sensor.
pros::vision_zero_e_t h_Sensors::vision_get_zero_point(void) {return m_vision_zero_point;}

/// Adds a signature to volatile memory for the Vision to use.
/// \param sig_id The signature ID to assign the signature to.
/// \param sig The address/pointer to the signature to use.
/// \return this* pointer for function chaining.
h_Sensors& h_Sensors::vision_set_signature(h_Sensors_Vision_Signatures sig_id, pros::vision_signature_s_t *sig)
{
    pros::c::vision_set_signature(m_s_vision, static_cast<std::uint8_t>(sig_id), sig);
}

/// Sets the zero-point mode of the Vision sensor.
/// \param zero_point The zero-point mode to use.
/// \return this* pointer for function chaining.
h_Sensors& h_Sensors::vision_set_zero_point(pros::vision_zero_e_t zero_point)
{
    pros::c::vision_set_zero_point(m_s_vision, zero_point);
}


//* IMU *//

/// \return The current IMU heading relative to starting position.
double h_Sensors::imu_get_heading(void) {return pros::c::imu_get_heading(m_s_imu);}

/// \return The current IMU rotation relative to starting position.
double h_Sensors::imu_get_rotation(void) {return pros::c::imu_get_rotation(m_s_imu);}

/// \return The current IMU pitch relative to starting position.
double h_Sensors::imu_get_pitch(void) {return pros::c::imu_get_pitch(m_s_imu);}

/// \return The current IMU roll relative to starting position.
double h_Sensors::imu_get_roll(void) {return pros::c::imu_get_roll(m_s_imu);}

/// \return The current IMU gyro readings in degrees/sec.
pros::c::imu_gyro_s_t h_Sensors::imu_get_gyro_readings(void) {return pros::c::imu_get_gyro_rate(m_s_imu);}

/// IMPORTANT: default mode for this function is g-force.
/// \return The current IMU acceleration.
pros::c::imu_accel_s_t h_Sensors::imu_get_accel_readings(h_Sensors_IMU_Accel_Mode mode)
{
    pros::c::imu_accel_s_t return_ {pros::c::imu_get_accel(m_s_imu)};
    if (mode == h_Sensors_IMU_Accel_Mode::METERS)
    {
        return_.x *= 9.80665;
        return_.y *= 9.80665;
        return_.z *= 9.80665;
    }
    return return_;
}

/// \return The current status of the IMU.
pros::c::imu_status_e h_Sensors::imu_get_status(void) {return pros::c::imu_get_status(m_s_imu);}


//* Tracking wheels *//

/// \param track_id The ID of the tracking wheel.
/// \return Distance the wheel traveled in encoder ticks.
int h_Sensors::tracking_wheels_get(h_Sensors_Tracking_Wheel_IDs track_id)
{
    switch (track_id)
    {
        case h_Sensors_Tracking_Wheel_IDs::LEFT:
            return pros::c::adi_encoder_get(m_adi_enc_l);
        case h_Sensors_Tracking_Wheel_IDs::RIGHT:
            return pros::c::adi_encoder_get(m_adi_enc_r);
        case h_Sensors_Tracking_Wheel_IDs::MIDDLE:
            return pros::c::adi_encoder_get(m_adi_enc_m);
    }
}

/// \return Wheelbase from left to right tracking wheels in inches.
double h_Sensors::tracking_wheels_get_wheelbase(void) {return m_tracking_wheel_wheelbase;}

/// \return Half of the left-to-right wheelbase.
double h_Sensors::tracking_wheels_get_side_radius(void) {return m_side_tracking_wheel_radius;}

/// \return Radius from midpoint of line the wheel is on to center of robot.
double h_Sensors::tracking_wheels_get_middle_radius(void) {return m_middle_tracking_wheel_radius;}

/// Resets all tracking wheels.
void h_Sensors::tracking_wheels_reset(void)
{
    pros::c::adi_encoder_reset(m_adi_enc_l);
    pros::c::adi_encoder_reset(m_adi_enc_r);
    pros::c::adi_encoder_reset(m_adi_enc_m);
}

/// Resets the specified tracking wheel.
/// \param track_id The ID of the tracking wheel.
void h_Sensors::tracking_wheels_reset(h_Sensors_Tracking_Wheel_IDs track_id)
{
    switch (track_id)
    {
        case h_Sensors_Tracking_Wheel_IDs::LEFT:
            pros::c::adi_encoder_reset(m_adi_enc_l);
            break;
        case h_Sensors_Tracking_Wheel_IDs::RIGHT:
            pros::c::adi_encoder_reset(m_adi_enc_r);
            break;
        case h_Sensors_Tracking_Wheel_IDs::MIDDLE:
            pros::c::adi_encoder_reset(m_adi_enc_m);
            break;
    }
}
