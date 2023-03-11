/*!
 *  \file   Point.cpp
 *  \brief  
 *  
 */


#include "Point.hpp"

Point::Point() : m_x(0), m_y(0)
{
}

Point::Point(int x, int y) : m_x(x), m_y(y)
{
}

int Point::x() const
{
    return m_x;
}

int Point::y() const
{
    return m_y;
}