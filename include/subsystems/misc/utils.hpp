//* 2020-2021-bionic-beaver
//* 
//* Author(s):      Dev Patel   <hello.devpatel@gmail.com>
//*                 Marco Tan   <marco.tan.200405@gmail.com>
//*             Neil Sachdeva   <Wiserlightning090@gmail.com>
//*
//* Desc:       Miscellaneous utilities

#ifndef UTILS_HPP
#define UTILS_HPP

//* API
#include "api.h"


//* Conversion functions *//

/// Degrees to radians
double u_deg_to_rad(double deg);
/// Radians to degrees
double u_rad_to_deg(double rad);


//* Time utilities *//

/// Timer utility.
class u_Timer
{
public:
    // Constructors and destructors

    u_Timer(void);
    ~u_Timer(void);


    // General methods

    std::uint32_t get_time(void);

private:
    const std::uint32_t start_time;

};

#endif  // UTILS_HPP
