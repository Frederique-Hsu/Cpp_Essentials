/*!
 *  \file       consteval_meta.cpp
 *  \brief      
 *  
 */


#include "consteval_meta.hpp"

#include <iostream>

consteval int factorial_sum(int n)
{
    int sum = 0;
    int fact = 1;
    for (int i = 1; i < n; ++i)
    {
        fact *= i;
        sum += fact;
    }
    return sum;
}


consteval FactorialSum::FactorialSum()
{
    int fact = 1;
    for (int i = 1; i < sizeof(sum)/sizeof(sum[0]); ++i)
    {
        fact *= i;
        sum[i] = sum[i-1] + fact;
    }
}

int FactorialSum::operator[](int i) const
{
    return sum[i];
}

void access_consteval_object()
{
    /* consteval */ FactorialSum obj;     /*! \note   'consteval' can only be used in function declaration. */
    for (int n; std::cin >> n; )
    {
        std::cout << "FactorialSum[" << n << "] = " << obj[n] << std::endl;
    }
}
