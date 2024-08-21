/*!
 *  \file       test_abstraction.c++
 *  \brief      
 *  
 */


#include <gtest/gtest.h>

#include "Shape.hpp"
#include "Circle.hpp"
#include "IrregularPolygon.hpp"
#include "../finalize.hpp"

TEST(UTest4Abstraction, CheckInterfaceInhertitance)
{
    Shape* pshape = new Circle(Point{3, 4}, 5);
    Shape* irregular_polygon = new IrregularPolygon{Point{1, 2},
                                                    Point{3, 4},
                                                    Point{5, 6},
                                                    Point{7, 8},
                                                    Point{9, 10}};
    auto deleter = finalize([&]() {
        delete pshape;
        delete irregular_polygon;
    });

    pshape->draw();
    irregular_polygon->rotate(5);
}