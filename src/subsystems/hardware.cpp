#include "subsystems/hardware.h"

/* Drive Motors */
// Drive, left front.
pros::Motor mLF { kHardware::k_mLF, mCart::E_MOTOR_GEARSET_18, false, mEnc::E_MOTOR_ENCODER_COUNTS };
// Drive, left back.
pros::Motor mLB { kHardware::k_mLB, mCart::E_MOTOR_GEARSET_18, false, mEnc::E_MOTOR_ENCODER_COUNTS };
// Drive, right front.
pros::Motor mRF { kHardware::k_mRF, mCart::E_MOTOR_GEARSET_18, false, mEnc::E_MOTOR_ENCODER_COUNTS };
// Drive, right back.
pros::Motor mRB { kHardware::k_mRB, mCart::E_MOTOR_GEARSET_18, false, mEnc::E_MOTOR_ENCODER_COUNTS };

/* Conveyor and Intake Motors */
// Intake, left.
pros::Motor mIL { kHardware::k_mIL, mCart::E_MOTOR_GEARSET_18, false, mEnc::E_MOTOR_ENCODER_COUNTS };
// Intake, right.
pros::Motor mIR { kHardware::k_mIR, mCart::E_MOTOR_GEARSET_18, false, mEnc::E_MOTOR_ENCODER_COUNTS };
// Conveyor, left.
pros::Motor mCB { kHardware::k_mCB, mCart::E_MOTOR_GEARSET_18, false, mEnc::E_MOTOR_ENCODER_COUNTS };
// Conveyor, right.
pros::Motor mCT { kHardware::k_mCT, mCart::E_MOTOR_GEARSET_18, false, mEnc::E_MOTOR_ENCODER_COUNTS };

/* Smart Sensors */
// Smart sensor, IMU.
pros::Imu sIMU { kHardware::k_sIMU };
// Smart sensor, Vision.
//pros::Vision sVision { kHardware::k_sVision };

/* Analog Sensors */
// Encoder, left.
pros::ADIEncoder aEncL { kHardware::k_aEncLT, kHardware::k_aEncLB, false };
// Encoder, right.
pros::ADIEncoder aEncR { kHardware::k_aEncRT, kHardware::k_aEncRB, false };
// Encoder. middle.
pros::ADIEncoder aEncM { kHardware::k_aEncMT, kHardware::k_aEncMB, false };
// Limit switch, ball detection.
//pros::ADIDigitalIn aLim { kHardware::k_aLim };