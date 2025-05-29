/*!
 *  \file       template_meta_programming.hpp
 *  \brief      
 *  
 */


#pragma once


template<int N> struct factorial
{
    enum 
    {
        value = N * factorial<N-1>::value
    };
};

template<> struct factorial<0>
{
    enum
    {
        value = 1
    };
};

constexpr int fact(int N)
{
    return N == 0 ? 1 : N * fact(N-1);
}