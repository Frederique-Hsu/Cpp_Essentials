/*!
 *  \file       class_hierarchies.cpp
 *  \brief      
 *  
 */


#include "class_hierarchies.hpp"

#include <iostream>

namespace generated_types
{
    void Shape::draw()
    {
        std::cout << "called Shape::draw()" << std::endl;
    }

    Triangle::Triangle(const Point& a, const Point& b, const Point& c)
    {
        three_points[0] = a;
        three_points[1] = b;
        three_points[2] = c;
    }

    void Triangle::draw()
    {
        std::cout << "called Triangle::draw()" << std::endl;
    }

    Circle::Circle() : m_center{0, 0}, m_radius{1.0} 
    {
    }

    Circle::Circle(const Point& center, double radius) : m_center{center}, m_radius{radius} 
    {
    }

    void Circle::draw()
    {
        std::cout << "called Circle::draw()" << std::endl;
    }
}