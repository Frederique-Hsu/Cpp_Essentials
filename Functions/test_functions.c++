/*!
 *  \file       test_functions.c++
 *  \brief
 *
 */


#include <gtest/gtest.h>

#include "functions.hpp"

TEST(UTester4Functions, CheckFactorial)
{
    EXPECT_EQ(factorial(1), 1);
    EXPECT_EQ(factorial(2), 2);
    EXPECT_EQ(factorial(3), 6);
    EXPECT_EQ(factorial(5), 120);
}

TEST(UTester4Functions, CheckConstExpression)
{
    constexpr int f9 = fac(9);      // 必须在编译时求值
    std::cout << "fac(9) = " << f9 << std::endl;
    EXPECT_EQ(362880, f9);

    int f5 = fac(5);    // 可能在编译时求值
    std::cout << "fac(5) = " << f5 << std::endl;

    int n = 8;
    int fn = fac(n);    // 在运行时求值（n是变量）
    std::cout << "fn = " <<  fn << std::endl;

    constexpr int f6 = fac(6);  // 必须在编译时求值
    // constexpr int fnn = fac(n); // 错误：无法确保在编译时求值，因为n是变量。
    std::cout << "f6 = " << f6 << std::endl;

    char array[fac(4)];     // 正确：数组的长度必须是常量，而fac()恰好是constexpr
    EXPECT_EQ(sizeof(array)/sizeof(char), 24);

    int count = 3;
    // char bad_array[fac(count)];     // 错误：数组的尺寸必须是常量，count是一个变量，fac(count)无法在编译器计算，只能在运行期计算，其是一个变量。
}


/*!
 *  \note   函数必须足够简单才能在编译时求值
 */
int glob;

/*!
 *  \warning    在C++11标准下，constexpr函数不能是void.
 *
constexpr void bad_constexpr_func(int a)
{
    glob = a;   // 错误： 在constexpr函数中，外部的变量有副作用。外部变量不能做到编译时计算。
}
 */

/*!
 *  \warning    在C++11标准下，constexpr函数必须只能包含一条独立的return语句.
 *
constexpr int bad_constexpr_func_with_multiple_returns(int a)
{
    if (a >= 0)
    {
        return a;
    }
    else
    {
        return -a;
    }
}
 */


/*!
 *  \warning    在C++11标准下，constexpr函数中不能有循环，也不能有局部变量。
 *
constexpr int bad_constexpr_func_with_for_loop(int a)
{
    int sum = 0;
    for (int i = 0; i < a; ++i)
    {
        sum += fac(i);
    }
    return sum;
}
 */

/*!
 *  \note   但在C++14以上标准时，以上关于constexpr函数的禁令失效。
 */
