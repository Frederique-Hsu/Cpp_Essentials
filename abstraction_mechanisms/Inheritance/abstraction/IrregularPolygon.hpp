/*!
 *  \file       IrregularPolygon.hpp
 *  \brief      
 *  
 */


#pragma once


#include "Polygon.hpp"

#include <initializer_list>
#include <list>

struct Point;

class IrregularPolygon : public Polygon
{
public:
    IrregularPolygon(std::initializer_list<Point>);

private:
    std::list<Point> m_points;

public:
    void draw() const override;
    void rotate(int) override;
};