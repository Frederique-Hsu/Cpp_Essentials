/*!
 *  \file       dynamic_dispatch.cpp
 *  \brief      
 *  
 */


#include "dynamic_dispatch.hpp"

#include <string>
#include <iostream>

bool dynamic_dispatch::Circle::intersect(const Shape& shape) const
{
    return shape.intersect(*this);
}

bool dynamic_dispatch::Circle::intersect(const Circle&) const
{
    std::cout << "Circle::intersect(circle, circle)" << std::endl;
    return true;
}

bool dynamic_dispatch::Circle::intersect(const Triangle&) const
{
    std::cout << "Circle::intersect(circle, triangle)" << std::endl;
    return true;
}

bool dynamic_dispatch::Triangle::intersect(const Shape& shape) const
{
    return shape.intersect(*this);
}

bool dynamic_dispatch::Triangle::intersect(const Circle&) const
{
    std::cout << "Triangle::interssect(triangle, circle)" << std::endl;
    return true;
}

bool dynamic_dispatch::Triangle::intersect(const Triangle&) const
{
    std::cout << "Triangle::intersect(triangle, triangle)" << std::endl;
    return true;
}

void dynamic_dispatch::intersect(Shape& s1, Shape& s2)
{
    if (s1.intersect(s2))
    {
        
    }
    else if (s2.intersect(s1))
    {
        
    }
}