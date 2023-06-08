/*!
 *  \file       statements.cpp
 *  \brief
 *
 */


#include "statements.hpp"

#include <iostream>
#include <iterator>

void check(E1 x, E2 y)
{
    if (x)
    {
        std::cout << "普通enum枚举值可先隐式转换成整数，然后再转换成bool类型" << std::endl;
    }
    if (y == E2::a)     // if (y)   // 错误： 无法转换成bool类型
    {
        std::cout << "但enum class不能" << std::endl;
    }
}

void problematic(Vessel v)
{
    /*!
     *  \note   在一种情况下不应该使用default: switch语句希望它的每个分支对应枚举类型中的一个枚举值。
     *          如果是这样的话，最好不要使用default语句，应该让编译器负责发现并报告case分支与枚举值
     *          未能完全匹配的问题。
     *
     *          如果在程序的后期维护和升级过程中，我们给枚举类型添加了一个新的枚举值。则很容易引发上述错误。
     */
    switch (v)
    {
    case Vessel::cup:
        std::cout << "cup" << std::endl;
        /*!
         *  \warning    C++允许在switch语句的块内部声明变量，但是不能初始化。
         */
        int x;          // 未初始化
        // int y = 3;      //  错误： 程序有可能跳过该声明（显式初始化）
        // std::string s;  // 错误： 程序有可能跳过该声明（隐式初始化）
        break;
    case Vessel::glass:
        std::cout << "glass" << std::endl;
        break;
    case Vessel::goblet:
        std::cout << "goblet" << std::endl;
        break;
#if 1
    case Vessel::chalice:
        std::cout << "chalice" << std::endl;
        break;
#else
    default:
        break;
#endif
    }
}

int sum(std::vector<int>& vec)
{
    int s = 0;
#if 0
    for (int elem : vec)
    {
        s += elem;
    }
#else
    for (auto p = std::begin(vec); p != std::end(vec); ++p)
    {
        s += *p;
    }
#endif
    return s;
}

void increment(std::vector<int>& vec)
{
    for (int& elem : vec)
    {
        ++elem;
    }
}
