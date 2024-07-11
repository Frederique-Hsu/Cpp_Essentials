/*!
 *  \file       Driver.cpp
 *  \brief
 *
 */


#include "Driver.hpp"

#include <iostream>

void Driver::calculator()
{
}

int& use_count()
{
    static int uc = 0;
    return uc;
}

void fn()
{
    std::cout << ++use_count() << std::endl;
}
