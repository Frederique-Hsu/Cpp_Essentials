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
    Shape() {}
    virtual ~Shape() {}

    Shape(const Shape&) = delete;
    Shape& operator=(const Shape&) = delete;

    Shape(Shape&&) = delete;
    Shape& operator=(Shape&&) = delete;
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

template<class Container, class Oper>
void for_all(Container& container, Oper op)
{
    for (auto& elem : container)
    {
        op(*elem);
    }
}