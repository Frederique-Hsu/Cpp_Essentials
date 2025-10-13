/*!
 *  \file       Functor.cpp
 *  \brief
 *
 */


#include "Functor.hpp"

#include <iostream>

Functor::Functor(int &imem) : imember{imem}
{
}

void Functor::operator()()
{
    auto doSomething = [](int i) {
        std::cout << "Do something..., i = " << i << std::endl;
    };

    for (unsigned index = 0; index < 1000000; ++index)
    {
        doSomething(imember);
    }
}
