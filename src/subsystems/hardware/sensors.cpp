//* Discobots 1104A comp code.
//* Marco Tan, Neil Sachdeva, Dev Patel
//*
//* File Created: 2020-09-29
//* Desc: Sensors class defintiions.


//* Headers
#include "main.h"   // Main header.


//* Definitions

/// struct - Analog sensor ports.
/// \param LT Top port of the left OSR.
/// \param RT Top port of the right OSR.
/// \param MT Top port of the middle OSR.
h_Analog_Sen_Ports::h_Analog_Sen_Ports(std::uint8_t LT, std::uint8_t RT, std::uint8_t MT)
    : pt_Enc_LT {LT}, pt_Enc_LB {++LT}, pt_Enc_RT {RT}, pt_Enc_RB {++RT} , pt_Enc_MT {MT} , pt_Enc_MB {++MT}
    {}

/// class - Sensors.  
//? This constructor has default values for all values besides the port numbers. 
//? You do not have to specify it all.
/// \param s_ports          Smart port numbers to assign.
/// \param a_ports          Analog port numbers to assign.
/// \param tw_w_left_rev    Reverse the left tracking wheel.
/// \param tw_w_right_rev   Reverse the right tracking wheel.
/// \param tw_w_middle_rev  Reverse the middle tracking wheel.
h_Sensors::h_Sensors(
        const h_Smart_Sen_Ports &s_ports, const h_Analog_Sen_Ports &a_ports,
        bool tr_w_left_rev, bool tr_w_right_rev, bool tr_w_middle_rev
    )
    : m_sVision {s_ports.pt_Vision}, m_sIMU {s_ports.pt_IMU}, 
      m_aL {a_ports.pt_Enc_LT, a_ports.pt_Enc_LB, tr_w_left_rev}, m_aR {a_ports.pt_Enc_RT, a_ports.pt_Enc_RB, tr_w_right_rev},
      m_aM {a_ports.pt_Enc_MT, a_ports.pt_Enc_MB, tr_w_middle_rev}
    {}

/// Initializes the sensors. 
//? Will take some time because of IMU reset.
void h_Sensors::initialize()
{
    /// IMU reset.
    m_sIMU.reset();

    /// Vision 
    m_sVision.clear_led();
    m_sVision.set_wifi_mode(0);

    // Tracking wheels.
    m_aL.reset();
    m_aR.reset();
    m_aM.reset();

    do {pros::delay(10);} while (m_sIMU.is_calibrating());
}

/// Add a signature to the Vision sensor's volatile memory.
/// \param sig The signature object to add.
/// \param ID The ID to assign to the signature.
h_Sensors& h_Sensors::add_sig(pros::vision_signature_s_t sig, h_sVision_IDs ID)
{
    m_sVision.set_signature(static_cast<std::uint32_t>(ID), &sig);
    return *this;
}

/// Get a Vision object from a signature.
/// \param size The size of the object to find.
/// \param ID The signature ID to look for.
/// \return A Vision sensor object.
pros::vision_object_s_t h_Sensors::get_obj_sig(int size, h_sVision_IDs ID)
{
    return m_sVision.get_by_sig(size, static_cast<std::uint32_t>(ID));
}

/// Get a Vision object from a size.
/// \param size The size of the object to find.
/// \return A Vision sensor object.
pros::vision_object_s_t h_Sensors::get_obj_siz(int size)
{
    return m_sVision.get_by_size(size);
}

/// Get the heading from the IMU
/// \return A heading value from 0 - 360 deg.
double h_Sensors::get_heading()
{
    return m_sIMU.get_heading();
}

/// Reset all the encoder values.
h_Sensors& h_Sensors::reset_enc()
{
    m_aL.reset();
    m_aR.reset();
    m_aM.reset();
    return *this;
}

/// Get encoder values based on the ID supplied.
/// \param ID The ID of the encoder to get values from.
/// \return Values in encoder ticks.
int32_t h_Sensors::get_enc(h_Encoder_IDs ID)
{
    switch (ID)
    {
    case h_Encoder_IDs::LEFT:
        return m_aL.get_value();
    case h_Encoder_IDs::RIGHT:
        return m_aR.get_value();
    case h_Encoder_IDs::MIDDLE:
        return m_aM.get_value();
    case h_Encoder_IDs::AVG_SIDES:
        return (m_aL.get_value() + m_aR.get_value()) / 2;
    default:
        return 0;
    }
}
