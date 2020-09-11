/* Discobots 1104A comp code.
 * Marco Tan, Neil Sachdeva
 * 
 * Code for initialization goes here.
 */

#include "main.h"

/* Disabled Function */
void disabled()
{

}

/* Comp Initialization Function */
void competition_initialize()
{

}

/* Initialize Function */
void initialize()
{
    // TODO: create auton selector
    // TODO: add necessary initialization
    mIL.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);
    mIR.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);
    mCT.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);
    mCB.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);
}