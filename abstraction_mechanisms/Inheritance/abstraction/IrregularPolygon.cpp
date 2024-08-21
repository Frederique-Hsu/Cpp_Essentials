/*!
 *  \file       IrregularPolygon.cpp
 *  \brief      
 *  
 */


#include "IrregularPolygon.hpp"
#include "Circle.hpp"

#ifdef DEBUG_WITH_LOG
    #include <iostream>
#endif

IrregularPolygon::IrregularPolygon(std::initializer_list<Point> points) : m_points(0)
{
    for (auto point : points)
    {
        m_points.push_back(point);
    }
}

void IrregularPolygon::draw() const
{
#ifdef DEBUG_WITH_LOG
    std::clog << "Called IrregularPolygon::draw() const" << std::endl;
#endif
}

void IrregularPolygon::rotate(int)
{
#ifdef DEBUG_WITH_LOG
    std::clog << "Called IrregularPolygon::rotate(int)" << std::endl;
#endif
}