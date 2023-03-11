/*!
 *  \file   Triangle.hpp
 *  \brief  
 *  
 */


#pragma once

#include "Shape.hpp"

class Triangle : public Shape
{
public:
    Triangle(Point p1, Point p2, Point p3);
private:
    Point m_p1;
    Point m_p2;
    Point m_p3;
public:
    Point center() const;
};