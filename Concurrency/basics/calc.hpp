/*!
 *  \file       calc.hpp
 *  \brief
 *
 */


#pragma once

// #define OBSERVE_MULTITHREAD_RUNNING

#include <vector>

void calculate(const std::vector<int>& vec, int* result);


class Calculator
{
public:
    Calculator(const std::vector<int>& numbers, int* result);
    void operator()();
private:
    const std::vector<int>& m_vec;
    int* m_result;
};
