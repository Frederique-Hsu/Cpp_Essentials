/*!
 *  \file       iteration_recursion.hpp
 *  \brief      
 *  
 */


#pragma once

#include <type_traits>

template<int N>
constexpr int factorial()
{
    return N * factorial<N-1>();
}

template<>
constexpr int factorial<1>()
{
    return 1;
}

constexpr int factorial(int i)
{
    return (i < 2) ? 1 : i * factorial(i-1);
}

template<int N>
struct Fac
{
    static const int value = N * Fac<N-1>::value;
};

template<>
struct Fac<1>
{
    static const int value = 1;
};

#define IF(condition, TrueType, FalseType)  std::condititonal<(condition), TrueType, FalseType>::type