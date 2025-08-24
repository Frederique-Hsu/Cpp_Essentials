/*!
 *  \file       Factorial.hpp
 *  \brief      
 *  
 */


#pragma once

#include <cstdint>

/*
 *  \struct     Factorial<N>
 *  \brief      递归定义： Factorial<N> = N * Factorial<N-1>
 */
template<int N>
struct Factorial
{
    static const int value = N * Factorial<N - 1>::value;
};


/*!
 *  \brief      特化： Factorial<0> = 1
 */
template<>
struct Factorial<0>
{
    static const int value = 1;
};

/*!
 *  \brief      Tail Recursion Optimization
 *              每次调用都不需要保留
 */
std::uint64_t factorial_iter(unsigned n, std::uint64_t accummulate = 1)
{
    if (n == 1)
    {
        return accummulate;
    }
    return factorial_iter(n - 1, accummulate * n);
}