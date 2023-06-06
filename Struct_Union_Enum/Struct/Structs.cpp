/*!
 *  \file       Structs.cpp
 *  \brief      
 *  
 */


#include "Structs.hpp"


Points::Points(Point p0)
{
    elements.push_back(p0);
}

Points::Points(Point p0, Point p1)
{
    elements.push_back(p0);
    elements.push_back(p1);
}

std::ostream& operator<<(std::ostream& os, Point p)
{
    os << "{" << p.x << ", " << p.y << "}";
    return os;
}