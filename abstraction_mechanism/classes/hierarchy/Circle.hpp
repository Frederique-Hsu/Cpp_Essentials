/*!
 *  \file   Circle.cpp
 *  \brief  
 *  
 */


#pragma once

#include "Shape.hpp"

class Circle : public Shape
{
public:
    Circle(Point origin, int radius);
private:
    Point m_origin;
    int m_radius;
public:
    Point center() const;
    void move(Point to);
    void draw() const;
    void rotate(int angle);
};