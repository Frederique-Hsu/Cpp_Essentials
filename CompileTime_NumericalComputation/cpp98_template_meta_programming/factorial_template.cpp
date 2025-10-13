/*!
 *  \file       factorial_template.cpp
 *  \brief      
 *  
 */


#include "factorial_template.hpp"

#include <iostream>

void print_template_factorial()
{
    // 数组a的元素值在编译期间就已经计算出来，不需要等到程序运行起来计算。
    const int a[] = { Factorial<0>::v,  Factorial<1>::v,  Factorial<2>::v, Factorial<3>::v, Factorial<4>::v,
                      Factorial<5>::v,  Factorial<6>::v,  Factorial<7>::v, Factorial<8>::v, Factorial<9>::v,
                     Factorial<10>::v, Factorial<11>::v, Factorial<12>::v};

    for (int n; std::cin >> n; )
    {
        std::cout << a[n] << std::endl;
    }
}

void print_template_factorial_enumerator()
{
    int array[] = { FactorialEnumerator<0>::v,  FactorialEnumerator<1>::v,  FactorialEnumerator<2>::v,
                    FactorialEnumerator<3>::v,  FactorialEnumerator<4>::v,  FactorialEnumerator<5>::v,
                    FactorialEnumerator<6>::v,  FactorialEnumerator<7>::v,  FactorialEnumerator<8>::v,
                    FactorialEnumerator<9>::v, FactorialEnumerator<10>::v, FactorialEnumerator<11>::v,
                   FactorialEnumerator<12>::v};
    for (int n; std::cin >> n; )
    {
        std::cout << array[n] << std::endl;
    }
}
