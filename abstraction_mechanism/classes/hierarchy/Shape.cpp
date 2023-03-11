/*!
 *  \file   Shape.cpp
 *  \brief  
 *  
 */


#include "Shape.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Smiley.hpp"

void rotate_all(std::vector<Shape*>& vec, int angle)
{
    for (auto& p : vec)
    {
        p->rotate(angle);
    }
}

#if 0
std::unique_ptr<Shape> read_shape(std::istream& is)
{
    Kind k;

    switch (k)
    {
    case Kind::circle:
        Point p(1, 2);
        int r = 3;
        return std::unique_ptr<Circle>(p, r);
    case Kind::triangle:
        Point p1(1, 2), p2(3, 4), p3(5, 6);
        return std::unique_ptr<Triangle>(p1, p2, p3);
    case Kind::smiley:
        Smiley* ps = std::unique<Smiley>(p, r);
        ps->add_eye(e1);
        ps->add_eye(e2);
        ps->set_mouth(m);
        return ps;
    }
}

void access()
{
    std::vector<Shape*> vec;
    while (std::cin)
    {
        vec.push_back(read_shape(std::cin));
    }
    rotate_all(vec, 45);
    for (auto p : vec)
    {
        delete p;
    }
}
#endif