/*!
 *  \file       functor.cpp
 *  \brief
 *
 */


#include "functor.hpp"

void increment(int& i)
{
    ++i;
}

Functor::Functor(int& i) : imem{i}
{
}

void Functor::operator()()
{
    for (unsigned index = 0; index < 1000000; ++index)
    {
        increment(imem);
    }
}
