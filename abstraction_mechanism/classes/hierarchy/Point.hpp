/*!
 *  \file   Point.hpp
 *  \brief  
 *  
 */


#pragma once

class Point
{
private:
    int m_x;
    int m_y;
public:
    Point();
    Point(int x, int y);
    Point(const Point& point);
    Point& operator=(const Point& point);

    int x() const;
    int y() const;
};

Point operator+(const Point& a, const Point& b);
Point operator-(const Point& a, const Point& b);
double distance(const Point& a, const Point& b);

bool operator==(const Point& a, const Point& b);
bool operator!=(const Point& a, const Point& b);