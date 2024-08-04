/*!
 *  \file       compute-areas.cpp
 *  \brief      This file implements the main() portal function for current project.
 *
 */


#include <cstdlib>
#include <iostream>

#include "geometry_circle.hpp"
#include "geometry_polygon.hpp"
#include "geometry_rhombus.hpp"
#include "geometry_square.hpp"


int main(int argc, char* argv[])
{
    std::cout << "Current C++ standard no. is " << __cplusplus << std::endl;
    std::cout << "Current program is " << sizeof(void*) * 8 << "-bits.\n" << std::endl;

    double radius = 2.5293;
    double circle_area = geometry::area::circle(radius);
    std::cout << "A circle of radius = " << radius
              << " has an area of " << circle_area << std::endl;

    int nsides = 19;
    double side = 1.29312;
    double polygon_area = geometry::area::polygon(nsides, side);
    std::cout << "A regular polygon of " << nsides
              << " sides of length " << side
              << " has an area of " << polygon_area << std::endl;

    double d1 = 5.0;
    double d2 = 7.8912;
    double rhombus_area = geometry::area::rhombus(d1, d2);
    std::cout << "A rhombus of major diagonal " << d1 << " and minor diagonal " << d2
              << " has an area of " << rhombus_area << std::endl;

    double len = 10.0;
    double square_area = geometry::area::square(len);
    std::cout << "A square of side " << len << " has an area of " << square_area << std::endl;

    return EXIT_SUCCESS;
}