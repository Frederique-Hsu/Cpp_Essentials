/*!
 *  \file   Triangle.cpp
 *  \brief  
 *  
 */


#include "Triangle.hpp"

Triangle::Triangle(Point p1, Point p2, Point p3)
    : m_p1(p1), m_p2(p2), m_p3(p3)
{
}

Point Triangle::center() const
{
    int x1 = m_p1.x();
    int x2 = m_p2.x();
    int y1 = m_p1.y();
    int y2 = m_p3.y();

    int center_x = (x1 + x2) / 2;
    int center_y = (y1 + y2) / 2;
    return Point(center_x, center_y);
}