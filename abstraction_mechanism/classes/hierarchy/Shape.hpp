/*!
 *  \file   Shape.hpp
 *  \brief  Define a class hierarchy, Shape is in the top hierarchy
 *  
 */


#pragma once

#include <vector>
#include <iostream>
#include <memory>

#include "Point.hpp"

class Shape
{
public:
    virtual ~Shape() {}
public:
    virtual Point center() const = 0;
    virtual void move(Point to) = 0;
    virtual void draw() const = 0;
    virtual void rotate(int angle) = 0;
};

void rotate_all(std::vector<Shape*>& v, int angle);

enum class Kind
{
    circle,
    triangle,
    smiley
};

std::unique_ptr<Shape> read_shape(std::istream& is);
void access();