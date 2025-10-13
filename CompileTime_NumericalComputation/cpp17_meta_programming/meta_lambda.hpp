/*!
 *  \file       meta_lambda.hpp
 *  \brief      研究C++17的 Lambda 元编程
 *  
 */


#pragma once


auto factorial_sum = [](int n) -> int
{
    int sum = 0;
    int fact = 1;
    for (int index = 1; index <= n; ++index)
    {
        fact *= index;
        sum += fact;
    }
    return sum;
};

void access_constexpr_lambda();

class A
{
    int a[5] = {0};
    
public:
    A(int c);
    
public:
    int operator()(int x, int y);
};

int q(int s, int t);

void lambda_capture_data();
