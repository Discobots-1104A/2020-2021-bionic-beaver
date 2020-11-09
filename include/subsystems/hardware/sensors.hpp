//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Sensors class declarations

//TODO: maybe add over sensors if we anticipate their use, like optical and ultrasonic

#ifndef SENSORS_HPP
#define SENSORS_HPP

#include "api.h"


/// User-defined literal for ADI ports later

std::uint8_t operator"" _ADI (char adi_port);

/// Vision sensor signatures enum
enum h_Sensors_Vision_Signatures
{
    RED_ID = 1,
    BLUE_ID,
    NULL_ID = 255
};

/// Vision sensor signature sets enum
enum class h_Sensors_Vision_Signature_Sets
{
    KARANS_HOME,
    CENTER
};

/// IMU acceleration mode
enum class h_Sensors_IMU_Accel_Mode
{
    METERS,
    GFORCE
};

/// Tracking wheel enum
enum class h_Sensors_Tracking_Wheel_IDs
{
    LEFT,
    RIGHT,
    MIDDLE
};

/// Sensors scales
struct h_Sensors_Scales
{
    // Vision sensor related
    struct h_Sensors_Vision_Scales
    {
                    double      m_vision_sensor_height; // Vision sensor height in inches
                    double      m_vision_sensor_angle;  // Vision sensor angle in degrees
        pros::vision_zero_e_t   m_vision_zero_point;    // Vision sensor zero point.
    } m_vision_scales;

    // Tracking wheel related
    struct h_Sensors_Tracking_Wheel_Scales
    {
        double m_tracking_wheel_wheelbase;      // Wheelbase from left to right tracking wheel
        double m_side_tracking_wheel_radius;    // Half of the left-to-right wheelbase
        double m_middle_tracking_wheel_radius;  // Radius from midpoint of line the wheel is on to center of robot
    } m_tracking_wheel_scales;
};

/// Smart ports
struct h_Sensors_Smart_Ports
{
    std::uint8_t    m_vision;   // Vision sensor
    std::uint8_t    m_imu;      // IMU
};

/// ADI ports and reversed states
struct h_Sensors_ADI_Config
{
    // Constructor for struct

    h_Sensors_ADI_Config(
        std::uint8_t enc_left_top, std::uint8_t enc_right_top, std::uint8_t enc_mid_top,
        bool enc_left_rev, bool enc_right_rev, bool enc_mid_rev
    );

    std::uint8_t    m_adi_enc_lt;   // Left encoder, top port
    std::uint8_t    m_adi_enc_lb;   // Left encoder, bottom port
    std::uint8_t    m_adi_enc_rt;   // Right encoder, top port
    std::uint8_t    m_adi_enc_rb;   // Right encoder, bottom port
    std::uint8_t    m_adi_enc_mt;   // Middle encoder, top port
    std::uint8_t    m_adi_enc_mb;   // Middle encoder, bottom port
    bool            m_adi_enc_l_reversed;   // If left encoder is reversed
    bool            m_adi_enc_r_reversed;   // If right encoder is reversed
    bool            m_adi_enc_m_reversed;   // If middle encoder is reversed
};

/// Sensors class. Contains all variables and member functions pertaining to 
/// the operation of all sensors.
class h_Sensors
{
public:
    // Constructor and destructor

    h_Sensors(
        const h_Sensors_Scales&         scales,
        const h_Sensors_Smart_Ports&    smart_ports,
        const h_Sensors_ADI_Config&     adi_ports
    );
    ~h_Sensors();


    // General methods

    h_Sensors& initialize(void);


    // Vision sensor

                    double  vision_get_sensor_height(void);
                    double  vision_get_sensor_angle(void);
    pros::vision_object_s_t vision_get_by_sig(int size, h_Sensors_Vision_Signatures sig_id);
    pros::vision_object_s_t vision_get_by_size(int size);
    pros::vision_zero_e_t   vision_get_zero_point(void);
                h_Sensors&  vision_set_signature(h_Sensors_Vision_Signatures sig_id, pros::vision_signature_s_t *sig);
                h_Sensors&  vision_set_zero_point(pros::vision_zero_e_t zero_point);


    // IMU

                    double  imu_get_heading(void);
                    double  imu_get_rotation(void);
                    double  imu_get_pitch(void);
                    double  imu_get_roll(void);
    pros::c::imu_gyro_s_t   imu_get_gyro_readings(void);
    pros::c::imu_accel_s_t  imu_get_accel_readings(h_Sensors_IMU_Accel_Mode mode = h_Sensors_IMU_Accel_Mode::GFORCE);
    pros::c::imu_status_e   imu_get_status(void);


    // Tracking wheels

    int     tracking_wheels_get(h_Sensors_Tracking_Wheel_IDs track_id);
    double  tracking_wheels_get_wheelbase(void);
    double  tracking_wheels_get_side_radius(void);
    double  tracking_wheels_get_middle_radius(void);
    void    tracking_wheels_reset(void);
    void    tracking_wheels_reset(h_Sensors_Tracking_Wheel_IDs track_id);


private:
    // Smart sensor port numbers
    const std::uint8_t  m_s_vision;     // Vision sensor
    const std::uint8_t  m_s_imu;        // IMU


    // ADI objects
    const pros::c::adi_encoder_t    m_adi_enc_l;    // Left encoder
    const pros::c::adi_encoder_t    m_adi_enc_r;    // Right encoder
    const pros::c::adi_encoder_t    m_adi_enc_m;    // Middle encoder


    // Vision sensor config
    const double    m_vision_sensor_height;         // Vision sensor height in inches
    const double    m_vision_sensor_angle;          // Vision sensor angle in degrees
    pros::vision_zero_e_t   m_vision_zero_point;    // Vision sensor zero point


    // Tracking wheel config
    const double    m_tracking_wheel_wheelbase;        // Wheelbase from left to right tracking wheel
    const double    m_side_tracking_wheel_radius;      // Half of the left-to-right wheelbase
    const double    m_middle_tracking_wheel_radius;    // Radius from midpoint of line the wheel is on to center of robot

};

#endif  //  SENSORS_HPP
