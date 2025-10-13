/*!
 *  \file       meta_class.cpp
 *  \brief      
 *  
 */


#include "meta_class.hpp"

#include <iostream>


/*!
 *  \note   C++14中可以很好地利用常量式构造函数来创建常量式对象，
 *          取用对象数据给常量式数组初始化。
 */
constexpr FactorialSum::FactorialSum()
{
    int fact = 1;
    for (int i = 1; i < 13; ++i)
    {
        fact *= i;
        sum[i] = sum[i-1] + fact;
    }
}
/*!
 *  \attention  在类外部实现类的 constexpr 构造函数或成员函数，仍然需要带上 constexpr 限定符。
 */
constexpr int FactorialSum::operator()(int i) const
{
    return sum[i];
}

constexpr int FactorialSum::operator[](int i) const
{
    return sum[i];
}

void create_constexpr_class()
{
    constexpr FactorialSum fact_sum;
    constexpr int array[] = {0,
         fact_sum(1),  fact_sum(2), fact_sum(3), fact_sum(4),  fact_sum(5),
         fact_sum(6),  fact_sum(7), fact_sum(8), fact_sum(9), fact_sum(10),
        fact_sum(11), fact_sum(12)};

    for (int n; std::cin >> n; )
    {
        std::cout << array[n] << std::endl;
    }
}

void print_constexpr_class_object()
{
    constexpr FactorialSum obj;     // 常量式对象，建立于程序运行之初，其初始化的构造函数计算在编译期完成。

    for (int n; std::cin >> n; )
    {
        /*! \attention  取用常量式对象的成员数据。
         *              常量式对象在程序运行之初，在内存中开辟了对象空间。把静态数据、初始化（常量式构造函数）、
         *              以及下标操作符[]封装在常量式对象中。
         */
        std::cout << obj[n] << std::endl;
    }
}
