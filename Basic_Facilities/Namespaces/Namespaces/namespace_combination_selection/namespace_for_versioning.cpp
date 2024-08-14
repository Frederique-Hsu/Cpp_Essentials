/*!
 *  \file       namespace_for_versioning.cpp
 *  \brief
 *
 */


#include "namespace_for_versioning.hpp"

#include <iostream>

double Popular::V3_2::fn(double)
{
    std::cout << "called Popular::V3_2::fn(double)" << std::endl;

    return double{};
}

int Popular::V3_2::fn(int)
{
    std::cout << "called Popular::V3_2::fn(int)" << std::endl;

    return int{};
}

double Popular::V3_0::fn(double)
{
    std::cout << "called Popular::V3_0::fn(double)" << std::endl;

    return double{};
}

double Popular::V2_4_2::fn(double)
{
    std::cout << "called Popular::V2_4_2::fn(double)" << std::endl;

    return double{};
}
