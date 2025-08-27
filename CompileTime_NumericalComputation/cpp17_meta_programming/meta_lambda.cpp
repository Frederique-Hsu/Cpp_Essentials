/*!
 *  \file       meta_lambda.cpp
 *  \brief      
 *  
 */


#include "meta_lambda.hpp"

#include <iostream>

void access_constexpr_lambda()
{
    constexpr int x3 = factorial_sum(3);
    std::cout << "x3 = " << x3 << std::endl;
    
    constexpr auto constexpr_lambda_obj3 = [](int n)
    {
        int sum = 0;
        int fact = 1;
        for (int index = 1; index <= n; ++index)
        {
            fact *= index;
            sum += fact;
        }
        return sum;
    }(3);
    std::cout << "constexpr_lambda_obj3 = " << constexpr_lambda_obj3 << std::endl;
}


A::A(int c)
{
    a[3] = 2 * c;
    a[4] = c + 1;
}

int A::operator()(int x, int y)
{
    return 2 * a[x] + a[y] * a[y];
}

int q(int s, int t)
{
    static int data[5] = {0, 0, 0, 16, 9};
    
    return 2 * data[s] + data[t] * data[t];
}

void lambda_capture_data()
{
    int b[5] = {0, 0, 0, 16, 9};
    
    auto f = [b](int x, int y)
    {
        return 2 * b[x] + b[y] * b[y];
    };
    
    A w(8);
    std::cout << "w(3, 4) = " << w(3, 4) << std::endl;
    std::cout << "f(3, 4) = " << f(3, 4) << std::endl;
    std::cout << "q(3, 4) = " << q(3, 4) << std::endl;
}
