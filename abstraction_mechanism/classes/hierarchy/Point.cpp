/*!
 *  \file   Point.cpp
 *  \brief  
 *  
 */


#include "Point.hpp"

#include <cmath>

Point::Point() : m_x(0), m_y(0)
{
}

Point::Point(int x, int y) : m_x(x), m_y(y)
{
}

Point::Point(const Point& point) : m_x(point.m_x), m_y(point.m_y)
{
}

Point& Point::operator=(const Point& point)
{
    if (this != &point)
    {
        m_x = point.m_x;
        m_y = point.m_y;
    }
    return *this;
}

int Point::x() const
{
    return m_x;
}

int Point::y() const
{
    return m_y;
}

Point operator+(const Point& a, const Point& b)
{
    return Point(a.x() + b.x(), a.y() + b.y());
}

Point operator-(const Point& a, const Point& b)
{
    return Point(a.x() - b.x(), a.y() - b.y());
}

double distance(const Point& a, const Point& b)
{
    double x_diff = std::pow(a.x() - b.x(), 2.0);
    double y_diff = std::pow(a.y() - b.y(), 2.0);

    return std::sqrt(x_diff + y_diff);
}

bool operator==(const Point& a, const Point& b)
{
    return (a.x() == b.x()) && (a.y() == b.y());
}

bool operator!=(const Point& a, const Point& b)
{
    return !(a == b);
}