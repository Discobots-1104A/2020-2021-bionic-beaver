#include "globals.hpp"

std::shared_ptr<okapi::ChassisController> chassis;
std::shared_ptr<okapi::AsyncMotionProfileController> profile_controller;

okapi::MotorGroup intakes {
    okapi::Motor{17, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::counts},
    okapi::Motor{7, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::counts}
};

okapi::Motor convey_top {8, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::counts};
okapi::Motor convey_bot {15, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::counts};

okapi::Controller controller {okapi::ControllerId::master};

auto_select sel_auto;