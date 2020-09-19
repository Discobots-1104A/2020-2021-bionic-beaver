// Discobots 1104A comp code.
// Marco Tan, Neil Sachdeva
// 
// Hardware objects and functions defined here.

#include "subsystems/hardware.h"

//> Drive Motors <//
// Drive, left front.
pros::Motor mLF { kHardware::k_mLF, mCart::E_MOTOR_GEARSET_18, false, mEnc::E_MOTOR_ENCODER_COUNTS };
// Drive, left back.
pros::Motor mLB { kHardware::k_mLB, mCart::E_MOTOR_GEARSET_18, false, mEnc::E_MOTOR_ENCODER_COUNTS };
// Drive, right front.
pros::Motor mRF { kHardware::k_mRF, mCart::E_MOTOR_GEARSET_18, true, mEnc::E_MOTOR_ENCODER_COUNTS };
// Drive, right back.
pros::Motor mRB { kHardware::k_mRB, mCart::E_MOTOR_GEARSET_18, true, mEnc::E_MOTOR_ENCODER_COUNTS };

//> Conveyor and Intake Motors <//
// Intake, left.
pros::Motor mIL { kHardware::k_mIL, mCart::E_MOTOR_GEARSET_06, false, mEnc::E_MOTOR_ENCODER_COUNTS };
// Intake, right.
pros::Motor mIR { kHardware::k_mIR, mCart::E_MOTOR_GEARSET_06, true, mEnc::E_MOTOR_ENCODER_COUNTS };
// Conveyor, Bottom.
pros::Motor mCB { kHardware::k_mCB, mCart::E_MOTOR_GEARSET_06, true, mEnc::E_MOTOR_ENCODER_COUNTS };
// Conveyor, Top.
pros::Motor mCT { kHardware::k_mCT, mCart::E_MOTOR_GEARSET_06, true, mEnc::E_MOTOR_ENCODER_COUNTS };

//> Smart Sensors <//
// Smart sensor, IMU.
pros::Imu sIMU { kHardware::k_sIMU };
// Smart sensor, Vision.
pros::Vision sVision { kHardware::k_sVision };

//> Analog Sensors <//
// Encoder, left.
pros::ADIEncoder aEncL { kHardware::k_aEncLT, kHardware::k_aEncLB, false };
// Encoder, right.
pros::ADIEncoder aEncR { kHardware::k_aEncRT, kHardware::k_aEncRB, false };
// Encoder. middle.
pros::ADIEncoder aEncM { kHardware::k_aEncMT, kHardware::k_aEncMB, false };
// Limit switch, ball detection.
pros::ADIDigitalIn aLim { kHardware::k_aLim };

//> Controllers <//
pros::Controller cMaster { cID::E_CONTROLLER_MASTER };

//> Vision Signatures <//
pros::vision_signature_s_t sigRed = pros::Vision::signature_from_utility
    (kHardware::k_Colour_Sig::RED, 
    kHardware::k_uMin_Red, kHardware::k_uMax_Red, kHardware::k_uAvg_Red,
    kHardware::k_vMin_Red, kHardware::k_vMax_Red, kHardware::k_vAvg_Red,
    kHardware::k_Range_Red, kHardware::k_Type_Red);

pros::vision_signature_s_t sigBlue = pros::Vision::signature_from_utility
    (kHardware::k_Colour_Sig::BLUE, 
    kHardware::k_uMin_Blu, kHardware::k_uMax_Blu, kHardware::k_uAvg_Blu,
    kHardware::k_vMin_Blu, kHardware::k_vMax_Blu, kHardware::k_vAvg_Blu,
    kHardware::k_Range_Blu, kHardware::k_Type_Blu);

//> Misc <//
kHardware::k_Colour_Sig op_Sorting_Colour{};        // Ball sorting colour.

//> Motor Control Functions <//
// These functions are for when we do not want to control 
// individual motors for a big subsystem like the drive.


// Move the drive motors with an integer voltage value from -127 to 127. 
//
// \param left
//      The voltage value for the left side motors.
// \param right
//      The voltage value for the right side motors.
auto kHardware::Drive_Voltage(int left, int right) -> void
{
    mLF = left;     mLB = left;
    mRF = right;    mRB = right;
}

// Move the drive motors with an integer velocity value from -200 to 200. 
//
// \param left
//      The velocity value for the left side motors.
// \param right
//      The velocity value for the right side motors.
auto kHardware::Drive_Velocity(int left, int right) -> void
{
    mLF.move(left);     mLB.move(left);
    mRF.move(right);    mRB.move(right);
}

// Control the intake and conveyor motors with an integer velocity value from -600 to 600. 
// These two subsystems usually work in tandem, so it's easier to control them together.
// 
// \param intake
//      The velocity value for the intake motors.
// \param convy1
//      The velocity value for the top conveyor motor.
// \param convy2
//      The velocity value for the bottom conveyor motor.
auto kHardware::Pow_Intake_Convy(int intake, int convy1, int convy2) -> void
{
    mIL.move_velocity(intake);      mIR.move_velocity(intake);
    mCT.move_velocity(convy1);      mCB.move_velocity(convy2);
}
