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

    int x() const;
    int y() const;
};