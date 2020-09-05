/* Discobots 1104A comp code.
 * Marco Tan, Neil Sachdeva
 * 
 * Hardware objects and functions declared here.
 */

#ifndef HARDWARE_H
#define HARDWARE_H

#include "main.h"

/* Type Aliases */
using mCart     = pros::motor_gearset_e;            // Type alias, motor cartridges.
using mEnc      = pros::motor_encoder_units_e;      // Type alias, motor encoder units.
using mBreak    = pros::motor_brake_mode_e;         // Type alias, motor break modes.
using cAnalog   = pros::controller_analog_e_t;      // Type alias, controller analog buttons.
using cDigital  = pros::controller_digital_e_t;     // Type alias, controller digital buttons.
using cID       = pros::controller_id_e_t;          // Type alias, controller ID.

/* Drive Motors */
extern pros::Motor mLF;  // Drive, left front.
extern pros::Motor mLB;  // Drive, left back.
extern pros::Motor mRF;  // Drive, right front.
extern pros::Motor mRB;  // Drive, right back.

/* Conveyor and Intake Motors */
extern pros::Motor mIL;  // Intake, left.
extern pros::Motor mIR;  // Intake, right.
extern pros::Motor mCB;  // Conveyor, bottom.
extern pros::Motor mCT;  // Conveyor, top.

/* Smart Sensors */
extern pros::Imu sIMU;            // Smart sensor, IMU.
//extern pros::Vision sVision;      // Smart sensor, Vision.

/* Analog Sensors */
extern pros::ADIEncoder aEncL;      // Encoder, left.
extern pros::ADIEncoder aEncR;      // Encoder, right.
extern pros::ADIEncoder aEncM;      // Encoder, middle.
//extern pros::ADIDigitalIn aLim;     // Limit switch, ball detection.

/* Controllers */
extern::pros::Controller cMaster;   // Conrtoller, master.

namespace kHardware
{
    /* Drive Port Numbers */
    inline constexpr int k_mLF{ 0 };    // Drive port, mLF.
    inline constexpr int k_mLB{ 0 };    // Drive port, mLB.
    inline constexpr int k_mRF{ 0 };    // Drive port, mRF.
    inline constexpr int k_mRB{ 0 };    // Drive port, mRB.

    /* Conveyor and Intake Port Numbers */
    inline constexpr int k_mIL{ 0 };    // Intake port, mIL.
    inline constexpr int k_mIR{ 0 };    // Intake port, mIR.
    inline constexpr int k_mCB{ 0 };    // Conveyor port, mCB.
    inline constexpr int k_mCT{ 0 };    // Conveyor port, mCT.

    /* Smart Sensor Port Numbers*/
    inline constexpr int k_sIMU{ 0 };         // Smart sensor, senIMU.
    //inline constexpr int k_sVision{ 0 };      // Smart sensor, senVision.
    
    /* Analog Sensor ADI Ports */
    inline constexpr int k_aEncLT{ 0 };     // Analog sensor, aEncL, top.
    inline constexpr int k_aEncLB{ 0 };     // Analog sensor, aEncL, bottom.
    inline constexpr int k_aEncRT{ 0 };     // Analog sensor, aEncR, top.
    inline constexpr int k_aEncRB{ 0 };     // Analog sensor, aEncR, bottom.
    inline constexpr int k_aEncMT{ 0 };     // Analog sensor, aEncM, top.
    inline constexpr int k_aEncMB{ 0 };     // Analog sensor, aEncM, bottom.
    //inline constexpr int k_aLim{ 0 };   // Analog sensor, aLim.

    /* Motor Control Functions */
    /* These functions are for when we do not want to control 
    * individual motors for a big subsystem like the drive.
    */

    auto Drive_Voltage(int left, int right) -> void;
    auto Drive_Velocity(int left, int right) -> void;
    auto Pow_Intake_Convy(int intake, int convy = 0) -> void;
}

#endif // HARDWARE_H