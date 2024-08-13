/*!
 *  \file   Container.cpp
 *  \brief  Implement some functions
 *  
 */


#include "Container.hpp"

#include <iostream>

void visit(Container& c)
{
    const int sz = c.size();

    for (int index = 0; index != sz; ++index)
    {
        std::cout << c[index] << std::endl;
    }
}