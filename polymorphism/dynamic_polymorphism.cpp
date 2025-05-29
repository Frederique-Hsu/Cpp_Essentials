/*!
 *  \file       dynamic_polymorphism.cpp
 *  \brief      
 *  
 */


#include "dynamic_polymorphism.hpp"

#include <iostream>

namespace dynamic_polymorphism
{
    void derived::doWork()
    {
        std::cout << "derived object pointer is calling derived::doWork() method." << std::endl;
    }
}