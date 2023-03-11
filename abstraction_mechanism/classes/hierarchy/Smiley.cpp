/*!
 *  \file   Smiley.cpp
 *  \brief  
 *  
 */


#include "Smiley.hpp"

Smiley::Smiley(Point p, int r) : Circle(p, r), mouth(nullptr)
{
}

Smiley::~Smiley()
{
    delete mouth;
    for (auto p : eyes)
    {
        delete p;
    }
}

void Smiley::add_eye(Shape* s)
{
    eyes.push_back(s);
}

void Smiley::draw() const
{
    Circle::draw();
    for (auto p : eyes)
    {
        p->draw();
    }
    mouth->draw();
}

void Smiley::move(Point to)
{
    Circle::move(to);
}

void Smiley::set_mouth(Shape* s)
{
    mouth = s;
}

void Smiley::wink(int i)
{
}