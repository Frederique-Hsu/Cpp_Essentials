/*!
 *  \file       function_arguments.cpp
 *  \brief
 *
 */


#include "function_arguments.hpp"

#include <cmath>
#include <iostream>

/*!
 *  \section        Implementation
 */

int* find(int* first, int* last, int v)
{
    while ((first != last) && (*first != v))
    {
        ++first;
    }
    return first;
}

float fsqrt(const float& val)
{
    return std::sqrt(val);
}

void update(float& val)
{
    val += 10.0;
}

void fnref(std::vector<int>&)
{
    std::cout << "called fnref(T&): 非const左值引用参数" << std::endl;
}

void fnref(const std::vector<int>&)
{
    std::cout << "called fnref(const T&): const左值引用参数" << std::endl;
}

void fnref(std::vector<int>&&)
{
    std::cout << "called fnref(T&&): 右值引用参数" << std::endl;
}
