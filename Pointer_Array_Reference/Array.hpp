/*!
 *  \file       Array.hpp
 *  \brief      研究C++的数组
 *
 */


#pragma once

#include <iostream>

/* Declaration ===================================================================================*/
template<typename T> int byte_diff(T* p, T* q);
template<typename T> void access(T elem);



/* Implementation ================================================================================*/
template<typename T> int byte_diff(T* p, T* q)
{
    return reinterpret_cast<char*>(q) - reinterpret_cast<char*>(p);
}

template<typename T> void access(T elem)
{
    std::cout << elem << std::endl;
}
