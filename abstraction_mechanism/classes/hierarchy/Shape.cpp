/*!
 *  \file   Shape.cpp
 *  \brief  
 *  
 */


#include "Shape.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"
#include "Smiley.hpp"

#include <memory>
#include <vector>

void rotate_all(std::vector<Shape*>& vec, int angle)
{
    for (auto& p : vec)
    {
        p->rotate(angle);
    }
}


std::unique_ptr<Shape> read_shape(std::istream& is)
{
    int x, y, r;
    is >> x >> y >> r;

    Kind k;
    // is >> k;

    Point p(x, y);
    Point p1(1, 2), p2(3, 4), p3(5, 6);
    
    std::unique_ptr<Shape> ps;
    switch (k)
    {
    case Kind::circle:
        ps = std::make_unique<Circle>(p, r);
        break;
    case Kind::triangle:
        ps = std::make_unique<Triangle>(p1, p2, p3);
        break;
    case Kind::smiley:
        ps = std::make_unique<Smiley>(p, r);
        // ps->add_eye(e1);
        // ps->add_eye(e2);
        // ps->set_mouth(m);
        break;
    }
    return ps;
}


void access()
{
    std::vector<std::unique_ptr<Shape>> vec;
    while (std::cin)
    {
        vec.push_back(read_shape(std::cin));
    }
    for_all(vec, [](Shape& shape){ shape.draw(); });        // draw_all()
    for_all(vec, [](Shape& shape){ shape.rotate(45); });    // rotate_all(45)
}