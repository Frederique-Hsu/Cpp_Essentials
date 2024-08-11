/*!
 *  \file       geometry_circle.cpp
 *  \brief
 *
 */


#include "geometry_circle.hpp"


#define _USE_MATH_DEFINES
#include <cmath>

double geometry::area::circle(double radius)
{
    return M_PI * std::pow(radius, 2);
}