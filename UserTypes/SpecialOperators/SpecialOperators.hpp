/*!
 *  \file       SpecialOperators.hpp
 *  \brief
 *
 */


#pragma once

#include <vector>
#include <string>
#include <complex>


struct Assoc
{
    std::vector<std::pair<std::string, int>> vec;

    const int& operator[](const std::string& key) const;
    int& operator[](const std::string& key);
};

struct Action
{
    int operator()(int);
    std::pair<int, int> operator()(int, int);
    double operator()(double);
};

class Add
{
    std::complex<double> val;
public:
    Add(std::complex<double> cplx);
    Add(double real, double imag);

public:
    void operator()(std::complex<double>& cmp) const;
};

namespace my
{
    template<typename Iter, typename Fnct>
    Fnct for_each(Iter begin, Iter end, Fnct fn)
    {
        while (begin != end)
        {
            fn(*begin++);
        }
        return fn;
    }
}

