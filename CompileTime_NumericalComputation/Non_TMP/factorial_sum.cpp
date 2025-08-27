/*!
 *  \file       factorial_sum.cpp
 *  \brief      
 *  
 */


#include "factorial_sum.hpp"

#include <iostream>

int factorial(int n)
{
    int t = 1;
    for (int i = 1; i <= n; i++)
    {
        t *= i;
    }
    return t;
}

void print_Factorial()
{
    std::cout << "Press Ctrl+D to quit or enter the value of n: ";
    for (int n; std::cin >> n;)
    {
        int s = 0;
        for (int i = 1; i <= n; i++)
        {
            s += factorial(i);
        }
        std::cout << "sum of factorial(" << n << ") = " << s << std::endl;
        std::cout << "Press Ctrl+D to quit or enter the value of n: ";
    }
}

int sumOfFactorial(int n)
{
    int sum = 0;

    for (int i = 1, t = 1; i <= n; t *= ++i)
    {
        sum += t;
    }
    return sum;
}

void print_SumOfFactorial()
{
    std::cout << "Press Ctrl+D to quit or enter the value of n: ";
    for (int n; std::cin >> n; )
    {
        std::cout << "sum of factorial(" << n << ") = " << sumOfFactorial(n) << std::endl;
        std::cout << "Press Ctrl+D to quit or enter the value of n: ";
    }
}

void print_OptimizedFactorialSum()
{
    int a[13] = {0};
    for (int i = 1, t = 1; i <= 12; t *= ++i)
    {
        a[i] += a[i-1] + t;
    }

    std::cout << "Press Ctrl+D to quit or enter the value of n: ";
    for (int n; std::cin >> n; )
    {
        std::cout << "sum of factorial(" << n << ") = " << a[n] << std::endl;
        std::cout << "Press Ctrl+D to quit or enter the value of n: ";
    }
}

/*!
 *  \brief      Sum of Factorial
 *  \version    Non_TMP_4.0
 *  \details    第一个部分涉及已知数组大小和元素求值计算，因独立于待处理的整数，所以可以看作静态数据而于运行之初
 *              预先计算设定。相当于下列实现：　
 */
void print_StaticFactorialSum()
{
    int a[13] = {       0,          1,            3,       9,       33,
                      153,        873,         5913,  4'6233,  40'9113,
                 403'7913,  4395'4713,  5'3395'6313};
    
    std::cout << "Press Ctrl+D to quit or enter the value of n: ";
    for (int n; std::cin >> n; )
    {
        std::cout << "sum of factorial(" << n << ") = " << a[n] << std::endl;
        std::cout << "Press Ctrl+D to quit or enter the value of n: ";
    }
}
