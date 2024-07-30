/*!
 *  \file       SpecialOperators.cpp
 *  \brief
 *
 */


#include "SpecialOperators.hpp"

#include <stdexcept>
#include <cmath>


const int& Assoc::operator[](const std::string& key) const
{
    for (auto& elem : vec)
    {
        if (elem.first == key)
        {
            return elem.second;
        }
    }
    throw std::invalid_argument("Not found the '" + key + "' from the vector");
}

int& Assoc::operator[](const std::string& key)
{
    for (auto& elem : vec)
    {
        if (elem.first == key)
        {
            return elem.second;
        }
    }
    vec.push_back(std::pair<std::string, int>{key, 0});

    return vec.back().second;
}

int Action::operator()(int arg)     // abs()
{
    return std::abs(arg);
}

std::pair<int, int> Action::operator()(int a, int b)    // generate a pair
{
    return std::pair<int, int>{a, b};
}

double Action::operator()(double num)
{
    return std::sqrt(num);
}


Add::Add(std::complex<double> cplx) : val{cplx}
{
}

Add::Add(double real, double imag) : val{real, imag}
{
}

void Add::operator()(std::complex<double>& cmp) const
{
    cmp += val;
}