//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Odometry class declarations

#ifndef ODOMETRY_HPP
#define ODOMETRY_HPP

//* API
#include "api.h"

//* Hardware
#include "subsystems/hardware/chassis.hpp"
#include "subsystems/hardware/sensors.hpp"

//* Misc
#include "subsystems/misc/utils.hpp"


enum class c_Robot_Starting_Pos_Side
{
    RED,
    BLUE,
    SKILLS
};

/// Tower center coords and optimal heading
/// Values based on Desmos field abstraction
struct c_Goal_Center_Coords
{
    double x;       // X coord in inches
    double y;       // Y coord in inches
    double head;    // Optimal heading in degrees
};

/// Ball center coords at start
/// Values based on Desmos field abstraction
struct c_Ball_Center_Coords
{
                        double  x;      // X coord in inches
                        double  y;      // Y coord in inches
    h_Sensors_Vision_Signatures colour; // Ball colour
};

/// Robot starting position based on turning center of robot
/// Values will deviate, but will also try to be corrected for
struct c_Robot_Starting_Pos_Coords
{
    double x;       // X coord in inches
    double y;       // Y coord in inches
    double head;    // Starting heading in degrees
};

/// Coordinates and optimal headings of all tower centers
struct c_All_Goal_Coords
{
    c_Goal_Center_Coords m_goal_a;  // Goal A
    c_Goal_Center_Coords m_goal_b;  // Goal B
    c_Goal_Center_Coords m_goal_c;  // Goal C
    c_Goal_Center_Coords m_goal_d;  // Goal D
    c_Goal_Center_Coords m_goal_e;  // Goal E
    c_Goal_Center_Coords m_goal_f;  // Goal F
    c_Goal_Center_Coords m_goal_g;  // Goal G
    c_Goal_Center_Coords m_goal_h;  // Goal H
    c_Goal_Center_Coords m_goal_I;  // Goal I
};

/// Starting coordinates of skills setup balls
/// Expect a 0.5 deviation from these values
struct c_Skills_Setup_Startup_Coords
{
    c_Ball_Center_Coords m_ball_a_b;    // Ball between Goals A-B
    c_Ball_Center_Coords m_ball_b_c;    // Ball between Goals B-C
    c_Ball_Center_Coords m_ball_b;      // Ball in front of Goal B
    c_Ball_Center_Coords m_ball_a_e;    // Ball between Goals A-E
    c_Ball_Center_Coords m_ball_c_f;    // Ball between Goals C-F
    c_Ball_Center_Coords m_ball_e_t;    // Ball top of Goal E
    c_Ball_Center_Coords m_ball_e_l;    // Ball left of Goal E
    c_Ball_Center_Coords m_ball_e_r;    // Ball right of Goal E
    c_Ball_Center_Coords m_ball_e_b;    // Ball bottom of Goal E
    c_Ball_Center_Coords m_ball_d_g;    // Ball between Goals D-G
    c_Ball_Center_Coords m_ball_f_i;    // Ball between Goals F-I
    c_Ball_Center_Coords m_ball_h;      // Ball in front of Goal H
    c_Ball_Center_Coords m_ball_g_h;    // Ball between Goals G-H
    c_Ball_Center_Coords m_ball_h_i;    // Ball between Goals H-I
};

/// Starting coordinates of live comp setup balls
/// Expect a 0.5 deviation from these values
struct c_Live_Comp_Setup_Startup_Coords
{
    c_Ball_Center_Coords m_ball_a;      // Ball in front of Goal A
    c_Ball_Center_Coords m_ball_b;      // Ball in front of Goal B
    c_Ball_Center_Coords m_ball_c;      // Ball in front of Goal C
    c_Ball_Center_Coords m_ball_e_t;    // Ball top of Goal E
    c_Ball_Center_Coords m_ball_e_l;    // Ball left of Goal E
    c_Ball_Center_Coords m_ball_e_r;    // Ball right of Goal E
    c_Ball_Center_Coords m_ball_e_b;    // Ball bottom of Goal E
    c_Ball_Center_Coords m_ball_h;      // Ball in front of Goal H
    c_Ball_Center_Coords m_ball_g;      // Ball in front of Goal G
    c_Ball_Center_Coords m_ball_i;      // Ball in front of Goal I
};

/// Struct of all robot starting positions
struct c_Robot_Starting_Positions
{
    c_Robot_Starting_Pos_Coords m_live_start_red;   // Starting position for live red
    c_Robot_Starting_Pos_Coords m_live_start_blue;  // Starting position for live blue
    c_Robot_Starting_Pos_Coords m_skills;           // Starting position for skills
};

/// Odometry class. Contains all variables and member functions pertaining to 
/// the operation of odometry. Callibration method should be ran at the beginning 
/// of program startup. Class automatically creates a thread to continuously update 
/// current position.
class c_Odometry
{
public:
    // Constructors and destructors

    c_Odometry(
        const c_Robot_Starting_Positions&       starting_coords,
        const c_All_Goal_Coords&                goal_coords,
        const c_Live_Comp_Setup_Startup_Coords& live_comp_coords,
        const c_Skills_Setup_Startup_Coords&    skills_comp_coords,
        h_Sensors*                  sensors_obj,
        h_Skid_Steer_Chassis*       chassis_obj,
        c_Robot_Starting_Pos_Side   starting_side
    );
    ~c_Odometry();


    // General methods

    void start_odom(void);
    void stop_odom(void);
    void calibrate(void);


    // Getter methods
                    double      get_x(void);
                    double      get_y(void);
                    double      get_angle(void);
                    double      get_rotation(void);
                    double      get_pitch(void);
                    double      get_roll(void);
    pros::c::imu_gyro_s_t       get_gyro_vals(void);
    pros::c::imu_accel_s_t      get_accel_vals(void);

private:
    // Starting position related values
    const c_Robot_Starting_Pos_Side     m_starting_side;    // Robot starting side
    double      m_starting_x;       // Robot starting X coord in inches
    double      m_starting_y;       // Robot starting Y coord in inches
    double      m_starting_rotate;  // Robot starting angle in degrees
    double      m_offset_x;         // Robot starting X offset in inches
    double      m_offset_y;         // Robot starting Y offset in inches
    double      m_offset_rotate;    // Robot starting angle offset in degrees


    // Field coords
    c_All_Goal_Coords                   m_goal_coords;          // Goal coords
    c_Live_Comp_Setup_Startup_Coords    m_live_comp_coords;     // Live comp ball coords
    c_Skills_Setup_Startup_Coords       m_skills_comp_coords;   // Skills comp ball coords 


    // References to other objects
    h_Sensors*                  m_sensors_obj;      // Sensors
    h_Skid_Steer_Chassis*       m_chassis_obj;      // Chassis


    // Global position values
    double      m_global_x {0.0};       // Robot global X coord in inches
    double      m_global_y {0.0};       // Robot global Y coord in inches
    double      m_global_angle {0.0};   // Robot global angle in degrees
    

    // Current position values
                    double  m_current_rotation {0.0};   // Robot current rotation in degrees
                    double  m_filtered_rotation {0.0};  // Filtered robot rotations in degrees
                    double  m_last_rotation {0.0};      // Previous robot rotations in degrees
                    double  m_current_pitch {0.0};      // Robot current pitch in degrees
                    double  m_filtered_pitch {0.0};     // Filtered robot pitch in degrees
                    double  m_last_pitch {0.0};         // Previous robot rotation in degrees
                    double  m_current_roll {0.0};       // Robot current roll in degrees
                    double  m_filtered_roll {0.0};      // Filtered robot roll in degrees
                    double  m_last_roll {0.0};          // Previous robot roll in degrees
    pros::c::imu_gyro_s_t   m_current_gyro_val;         // Robot current gyro values in degrees/sec
    pros::c::imu_accel_s_t  m_current_accel_vals;       // Robot current acceleration values in m/s2


    // local position values
    double m_len_right {0.0};       // Distance right tracking wheel travelled in inches
    double m_len_middle {0.0};      // Distance middle tracking wheel travelled in inches
    double m_delta_right {0.0};     // Change in right distance from last calculated distance
    double m_delta_middle {0.0};    // Change in middle distance from last calculated distance
    double m_prev_right {0.0};      // Previous right distance value
    double m_prev_middle {0.0};     // Previous middle distance value
    double m_delta_theta {0.0};     // Change in rotation from last recorded distance
    double m_alpha {0.0};           // Used for chord calc and offset later
    double m_radius_right {0.0};    // Right radius
    double m_radius_middle {0.0};   // Middle radius
    double m_chord_right {0.0};     // Right chord
    double m_chord_middle {0.0};    // Middle chord
    double m_polar_offset {0.0};    // Angle + robot angle


    // Update task
    pros::Task *m_update_task {nullptr};
    void m_update_func(void);
    double m_filter_values(double current_val, double last_val);

};

#endif  // ODOMETRY_HPP
