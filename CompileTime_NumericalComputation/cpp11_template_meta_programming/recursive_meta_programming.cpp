/*!
 *  \file       recursive_meta_programming.cpp
 *  \brief      
 *  
 */


#include "recursive_meta_programming.hpp"

#include <iostream>

/*!
 *  \details    C++11新增了编译期的常量式 (constexpr) 对象，和常量式函数（或称元函数）。
 *              常量式有些限制，特别要求常量式函数具有返回值，且函数体内当且仅当只有一条返回语句。
 *              常量式函数不允许返回void.
 *              常量式函数的作用，除了可以传递常量式参数，简单表达式求值，再就是模拟模板元编程中的递归推演模板。
 * 
 *  \note       C++11虽然也将常量式拓宽到浮点数和类对象，但是编译期数值计算能力并没有实质性提升。
 *              常量式作为非模板元素，但却是编译器计算。
 */
constexpr int Factorial(int n)
{
#if true
    return (n == 1) ? 1 : (Factorial(n-1) * n);
#else
    /*!
     *  \attention  Multiple return statement in constexpr function is a C++14 extension
     */
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return Factorial(n-1) * n;
    }
#endif
}

constexpr int SumOfFactorial(int n)
{
    return (n <= 1) ? n : SumOfFactorial(n-1) + Factorial(n);
}

void print_factorial_sum()
{
    int array[] = {                 0,  SumOfFactorial(1),  SumOfFactorial(2), SumOfFactorial(3), SumOfFactorial(4),
                    SumOfFactorial(5),  SumOfFactorial(6),  SumOfFactorial(7), SumOfFactorial(8), SumOfFactorial(9),
                   SumOfFactorial(10), SumOfFactorial(11), SumOfFactorial(12)};

    for (int n; std::cin >> n; )
    {
        std::cout << array[n] << std::endl;
    }
}
