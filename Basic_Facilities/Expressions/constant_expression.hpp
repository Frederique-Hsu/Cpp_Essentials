/*!
 *  \file       constant_expression.hpp
 *  \brief
 *
 */


#pragma once

#include <cmath>

/* Prototype =====================================================================================*/
struct Point
{
    int x;
    int y;
    int z;

    constexpr Point up(int d) const;
    constexpr Point move(int dx, int dy) const;
};

constexpr int square(int x);
constexpr int radial_distance(Point p);


/* Implementation ================================================================================*/
constexpr Point Point::up(int d) const
/*!
 *  \warning    constexpr成员函数须加上const限定，否则出现"member function has type of const,
 *              but function is not marked const"的编译错误。
 */
{
    return {x, y, z + d};
}

constexpr Point Point::move(int dx, int dy) const
{
    return {x+dx, y+dy, z};
}

/*!
 *  \note   constexpr函数一般只作为内联函数，其原型和实现都要放在header文件中。
 *          若将constexpr函数原型和函数实现分置在.hpp和.cpp文件中，在其他文件中调用此constexpr函数则会
 *          出现"constexpr function used before its definition"的编译错误。
 */
constexpr int square(int x)
{
    return x * x;
}

constexpr int radial_distance(Point p)
{
    return std::sqrt(square(p.x) + square(p.y) + square(p.z));
}
