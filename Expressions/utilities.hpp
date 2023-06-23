/*!
 *  \file       utilities.hpp
 *  \brief
 *
 */


#pragma once

constexpr int is_sqrt_helper(int sq, int d, int a)
{
    return ((sq <= a) ? is_sqrt_helper(sq + d, d + 2, a) : d);
}

constexpr int is_sqrt(int x)
{
    return is_sqrt_helper(1, 3, x)/2 - 1;
}
