/*!
 *  \file       Circle.hpp
 *  \brief      
 *  
 */


#pragma once

#include "Shape.hpp"

struct Point
{
    int     x;
    int     y;
};

class Circle : public Shape
{
public:
    Circle(Point point, int r);
    ~Circle() = default;

private:
    Point center;
    int radius;

public:
    void rotate(int) override;
    void draw() const override;
    bool is_closed() const override;
};