/*!
 *  \file   Smiley.hp
 *  \brief  
 *  
 */

#pragma once

#include "Circle.hpp"

#include <vector>

class Smiley : public Circle
{
public:
    Smiley(Point p, int r);
    ~Smiley();
private:
    std::vector<Shape*> eyes;
    Shape* mouth;
public:
    void move(Point to);
    void draw() const;

    void add_eye(Shape* s);
    void set_mouth(Shape* s);
    virtual void wink(int i);
};