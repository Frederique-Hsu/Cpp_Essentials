/*!
 *  \file       list.hpp
 *  \brief
 *
 */


#pragma once

#include <initializer_list>

struct S
{
    int a;
    int b;
};

struct SS
{
    double a;
    double b;
};

void f(S);

void g(S);
void g(SS);

template<class T> T square(T x)
{
    return x * x;
}

int high_value(std::initializer_list<int> val);
