/*!
 *  \file       list.cpp
 *  \brief
 *
 */


#include "list.hpp"

#include <iostream>
#include <type_traits>
#include <numeric>

void f(S)
{
    std::cout << "f(S)接受一个S" << std::endl;
}

void g(S)
{
    std::cout << "g(S)接受S结构体作为参数" << std::endl;
}

void g(SS)
{
    std::cout << "g(SS)重载SS结构体参数" << std::endl;
}

int high_value(std::initializer_list<int> val)
{
    int high = std::numeric_limits<int>::lowest();
    std::cout << "high = " << high << std::endl;

    if (val.size() == 0)
    {
        return high;
    }
    for (auto& elem : val)
    {
        if (elem > high)
            high = elem;
    }
    return high;
}
