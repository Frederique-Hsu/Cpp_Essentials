/*!
 *  \file       type_identification.cpp
 *  \brief      
 *  
 */


#include "type_identification.hpp"

#include <iostream>

void Polymorph::access()
{
    std::cout << "called virtual void Polymorph::access()" << std::endl;
}

void NonPolymorph::access()
{
    std::cout << "called NonPolymorph::access()" << std::endl;
}

void Derived::access()
{
    std::cout << "called void Derived::access() override" << std::endl;
}

void NonObject::access()
{
    std::cout << "called void NonObject::visit()" << std::endl;
}