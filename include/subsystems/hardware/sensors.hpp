//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-29
//* Desc: Sensors class declarations.

//! Prefix all objects here with "h_" except for child members and namespaces.

#ifndef H_SENSORS_HPP
#define H_SENSORS_HPP

//* Headers
#include "api.h"

//* User-defined types

/// enum - Vision Sensor IDs
enum class h_sVision_IDs
{
    RED_ID = 1,
    BLUE_ID
};

/// enum - Encoder IDs
enum class h_Encoder_IDs
{
    LEFT,
    RIGHT,
    MIDDLE,
    AVG_SIDES
};

/// struct - Smart sensor ports.
//? In order of: IMU, Vision
struct h_Smart_Sen_Ports
{
    std::uint8_t pt_IMU;    // Smart sensor port, IMU.
    std::uint8_t pt_Vision; // Smart sensor port, Vision.
};

/// struct - Analog sensor ports. 
//! Use only the top port number. 
//? In order of: Left tracking wheel, right tracking wheel, middle tracking wheel. 
struct h_Analog_Sen_Ports
{
    std::uint8_t pt_Enc_LT; // Analog port, encoder left top.
    std::uint8_t pt_Enc_LB; // Analog port, encoder left bottom.
    std::uint8_t pt_Enc_RT; // Analog port, encoder right top.
    std::uint8_t pt_Enc_RB; // Analog port, encoder right bottom.
    std::uint8_t pt_Enc_MT; // Analog port, encoder middle top.
    std::uint8_t pt_Enc_MB; // Analog port, encoder middle bottom.

    h_Analog_Sen_Ports(std::uint8_t LT, std::uint8_t RT, std::uint8_t MT);
};

/// class - Sensors
/// Has all the necessary objects and functions.
class h_Sensors
{
public:
    h_Sensors(
        const h_Smart_Sen_Ports &s_ports,
        const h_Analog_Sen_Ports &a_ports,
        bool tr_w_left_rev = false,
        bool tr_w_right_rev = true,
        bool tr_w_middle_rev = false
    );

    void initialize();

    h_Sensors& add_sig(pros::vision_signature_s_t sig, h_sVision_IDs ID);
    pros::vision_object_s_t get_obj_sig(int size, h_sVision_IDs ID);

    double get_heading();

    h_Sensors& reset();
    int32_t get_enc(h_Encoder_IDs ID);


private:
    pros::Vision m_sVision;
    pros::Imu m_sIMU;
    pros::ADIEncoder m_aL;
    pros::ADIEncoder m_aR;
    pros::ADIEncoder m_aM;

};

#endif  // H_SENSORS_HPP
