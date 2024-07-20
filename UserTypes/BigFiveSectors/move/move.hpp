/*!
 *  \file       move.hpp
 *  \brief      
 *  
 */


#pragma once

#include <utility>

template<class T> void swap(T& a, T& b)
{
    T tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}