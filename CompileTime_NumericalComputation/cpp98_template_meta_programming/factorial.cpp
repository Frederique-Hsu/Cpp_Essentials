/*!
 *  \file       factorial.cpp
 *  \brief      
 *  
 */


#include "factorial.hpp"

#include <iostream>

/*!
 *  \brief      Sum of factorial
 *  \version    Recur_1.0
 *  \details    阶乘和 (0 < n < 13) 的函数计算，可以递归实现。
 */
A x = {0, 1};

A factorial(int n)
{
    if (n == 0)
    {
        return x;
    }

    A y = factorial(n-1);
    y.t *= n;
    y.v += y.t;

    return y;
}

void print_factorial()
{
    for (int n; std::cin >> n;)
    {
        std::cout << factorial(n).v << std::endl;
    }
}


/*!
 *  \brief      sum of factorial
 *  \version    Recur_2.0
 *  \details    
 */
int static_factorial(int n)
{
    static int t = 1;
    if (n == 0)
    {
        t = 1;
        return 0;
    }
    return static_factorial(n-1) + (t *= n);
}

void print_static_factorial()
{
    for (int n; std::cin >> n; )
    {
        std::cout << static_factorial(n) << std::endl;
    }
}