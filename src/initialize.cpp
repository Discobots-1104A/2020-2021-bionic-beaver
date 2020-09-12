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

    /* Set the break modes to hold on the conveyor and intake motors. */
    mIL.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);
    mIR.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);
    mCT.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);
    mCB.set_brake_mode(mBreak::E_MOTOR_BRAKE_HOLD);

    /* Vision sensor initialization. */
    sVision.clear_led();                                                // Clear the Vision sensor LED.
    sVision.set_wifi_mode(false);                                       // Disable WiFi capabilities.
    sVision.set_signature(kHardware::k_Colour_Sig::RED, &sigRed);       // Set the signature ID for red signature.
    sVision.set_signature(kHardware::k_Colour_Sig::BLUE, &sigBlue);     // Likewise but for blue signature.
    
}