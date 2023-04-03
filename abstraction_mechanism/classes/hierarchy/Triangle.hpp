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
    Point gravity_center_point();
    Point ortho_center_point();
    Point circum_center_point();
    Point inner_center_point();
    double area();
    double perimeter();
public:
    Point center() const override;
    void move(Point to) override;
    void draw() const override;
    void rotate(int angle) override;
};