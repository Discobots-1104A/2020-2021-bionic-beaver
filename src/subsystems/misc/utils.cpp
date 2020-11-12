//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Miscellaneous utilities

#include "subsystems/misc/utils.hpp"


//* Conversion functions *//

double u_deg_to_rad(double deg) {return deg * M_PI / 180.0;}
double u_rad_to_deg(double rad) {return rad / M_PI * 180.0;}


//* Time utilities *//

u_Timer::u_Timer(void) : start_time{pros::millis()} 
{
    std::cout << "[U_TIMER] Timer started at: " << start_time << '\n';
}

u_Timer::~u_Timer(void)
{
    std::cout << "[U_TIMER] Timer ended at: " << pros::millis() << '\n';
}

std::uint32_t u_Timer::get_time(void)
{
    return pros::millis() - start_time;
}
