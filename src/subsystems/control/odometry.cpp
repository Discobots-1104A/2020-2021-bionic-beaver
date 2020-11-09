//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Odometry class definitions

#include "main.h"


//* Constructor and destructors *//

/// Odometry constructor. No default parameters, all parameters must be specified. 
/// \param starting_coords Struct with all starting coordinates.
/// \param goal_coords Coords of the center of each goal.
/// \param live_comp_coords Coords of the starting center of each ball during live comp.
/// \param skills_comp_coords Coords of the starting center of each ball during skills.
/// \param sensors_obj Reference to sensors object.
/// \param chassis_obj Reference to chassis object.
/// \param starting_side Which side the robot is starting on on the field.
c_Odometry::c_Odometry
(
    const c_Robot_Starting_Positions&       starting_coords,
    const c_All_Goal_Coords&                goal_coords,
    const c_Live_Comp_Setup_Startup_Coords& live_comp_coords,
    const c_Skills_Setup_Startup_Coords&    skills_comp_coords,
    h_Sensors&                  sensors_obj,
    h_Skid_Steer_Chassis&       chassis_obj,
    g_Robot_Starting_Pos_Side   starting_side
)   : m_starting_side{starting_side}, m_sensors_obj{sensors_obj}, m_chassis_obj{chassis_obj},
      m_goal_coords{goal_coords}, m_live_comp_coords{live_comp_coords}, m_skills_comp_coords{skills_comp_coords}
{
    switch (m_starting_side)
    {
    case g_Robot_Starting_Pos_Side::RED:
        m_starting_x = starting_coords.m_live_start_red.x;
        m_starting_y = starting_coords.m_live_start_red.y;
        m_starting_rotate = starting_coords.m_live_start_red.head;
        break;
    case g_Robot_Starting_Pos_Side::BLUE:
        m_starting_x = starting_coords.m_live_start_blue.x;
        m_starting_y = starting_coords.m_live_start_blue.y;
        m_starting_rotate = starting_coords.m_live_start_blue.head;
        break;
    case g_Robot_Starting_Pos_Side::SKILLS:
        m_starting_x = starting_coords.m_skills.x;
        m_starting_y = starting_coords.m_skills.y;
        m_starting_rotate = starting_coords.m_skills.head;
        break;
    }
}


//* General methods *//

/// Start the odometry task.
void c_Odometry::start_odom(void)
{
    m_update_task = new pros::Task(m_update_func);
}

/// Stop the odometry task.
void c_Odometry::stop_odom(void)
{
    if (m_update_task != nullptr)
    {
        m_update_task->remove();
        delete m_update_task;
        m_update_task = nullptr;
    }
}

/// Calibrate odometry.
void c_Odometry::calibrate(void)
{

}


//* Getter methods *//

/// \return Current X coord in inches.
double c_Odometry::get_x(void) {return m_global_x;}

/// \return Current Y coord in inches.
double c_Odometry::get_y(void) {return m_global_y;}

/// \return Current angle in degrees.
double c_Odometry::get_angle(void) {return m_global_angle;}

/// \return Current rotations in degrees.
double c_Odometry::get_rotation(void) {return m_current_rotation;}

/// \return Current pitch in degrees.
double c_Odometry::get_pitch(void) {return m_current_pitch;}

/// \return Current roll in degrees.
double c_Odometry::get_roll(void) {return m_current_roll;}

/// \return Gyro values in degrees/sec.
pros::c::imu_gyro_s_t c_Odometry::get_gyro_vals(void) {return m_current_gyro_val;}

/// \return Accelerometer values in m/s2
pros::c::imu_accel_s_t c_Odometry::get_accel_vals(void) {return m_current_accel_vals;}


//* Private methods *//

/// Updates odometry values.
void c_Odometry::m_update_func(void)
{
    while(true)
    {
        // Getting rotation, pitch, and roll
        m_current_rotation = m_sensors_obj.imu_get_rotation();
        m_filtered_rotation += [](double a, double b){
            double x = a - b; 
            if (std::fabs(x) < 0.01) {x = 0;} 
            return x;
        }(m_current_rotation, m_last_rotation);
        m_last_rotation = m_current_rotation;

        m_current_pitch = m_sensors_obj.imu_get_pitch();
        m_filtered_pitch += [](double a, double b){
            double x = a - b; 
            if (std::fabs(x) < 0.01) {x = 0;} 
            return x;
        }(m_current_pitch, m_last_pitch);
        m_last_pitch = m_current_pitch;

        m_current_roll = m_sensors_obj.imu_get_roll();
        m_filtered_roll += [](double a, double b){
            double x = a - b; 
            if (std::fabs(x) < 0.01) {x = 0;} 
            return x;
        }(m_current_roll, m_last_roll);
        m_last_pitch = m_current_pitch;

        // Find out the length each encoder moved.
        m_len_right = m_sensors_obj.tracking_wheels_get(h_Sensors_Tracking_Wheel_IDs::RIGHT) / 360.0 \
                      * (m_sensors_obj.tracking_wheels_get_side_radius() * M_PI);
        m_len_middle = m_sensors_obj.tracking_wheels_get(h_Sensors_Tracking_Wheel_IDs::MIDDLE) / 360.0 \
                       * (m_sensors_obj.tracking_wheels_get_middle_radius() * M_PI);
    
        // Find the change since last update.
        m_delta_right = m_len_right - m_prev_right;
        m_delta_middle = m_len_middle - m_prev_middle;

        // Update previous values.
        m_prev_right = m_len_right;
        m_prev_right = m_len_middle;

        // Determine change in angle
    }
}
