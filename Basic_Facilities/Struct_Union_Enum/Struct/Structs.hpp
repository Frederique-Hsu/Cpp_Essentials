/*!
 *  \file       Structs.hpp
 *  \brief
 *
 */


#pragma once

#include <vector>
#include <iostream>

#if 0
    struct Readout
    {
        char hour;
        int value;
        char seq;
    };
#else
    struct Readout
    {
        int value;
        char hour;
        char seq;
    };
#endif

template<typename ElemType>
struct Link
{
    ElemType    element;
    Link*       previous;
    Link*       successor;
};


struct Point
{
    int x;
    int y;
};

std::ostream& operator<<(std::ostream& os, Point p);

struct Points
{
    std::vector<Point> elements;    /* 必须至少包含一个Point */
    
    Points(Point p0);
    Points(Point p0, Point p1);
};