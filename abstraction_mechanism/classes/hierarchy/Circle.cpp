/*!
 *  \file   Circle.cpp
 *  \brief  
 *  
 */


#include "Circle.hpp"

Circle::Circle(Point origin, int radius) : m_origin(origin), m_radius(radius)
{
}

Point Circle::center() const
{
    return m_origin;
}

void Circle::move(Point to)
{
    m_origin = to;
}

void Circle::draw() const
{
}

void Circle::rotate(int angle)
{
}