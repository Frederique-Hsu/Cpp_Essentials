/*!
 *  \file       geometry_polygon.cpp
 *  \brief
 *
 */


#include "geometry_polygon.hpp"


#define _USE_MATH_DEFINES
#include <cmath>


double geometry::area::polygon(int nsides, double side)
{
    double perimeter = nsides * side;
    double apothem = side / (2.0 * std::tan(M_PI / nsides));

    return (perimeter * apothem) / 2.0;
}