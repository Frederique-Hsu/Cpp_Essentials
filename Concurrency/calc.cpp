/*!
 *  \file       calc.cpp
 *  \brief
 *
 */


#include "calc.hpp"

#if defined (OBSERVE_MULTITHREAD_RUNNING)
    #include <iostream>
#endif

void calculate(const std::vector<int>& vec, int* result)
{
    int sum = 0;
    for (auto& number : vec)
    {
        sum += number;
#if defined (OBSERVE_MULTITHREAD_RUNNING)
        std::cout << "Odd numbers - intermediate sum: " << sum << std::endl;
#endif
    }
    *result = sum;
}


Calculator::Calculator(const std::vector<int>& numbers, int* result)
    : m_vec(numbers), m_result(result)
{
}

void Calculator::operator()()
{
    int sum = 0;
    for (auto& number : m_vec)
    {
        sum += number;
#if defined (OBSERVE_MULTITHREAD_RUNNING)
        std::cout << "Even numbers - intermediate sum: " << sum << std::endl;
#endif
    }
    *m_result = sum;
}
