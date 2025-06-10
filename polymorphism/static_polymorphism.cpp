/*!
 *  \file       static_polymorphism.cpp
 *  \brief      
 *  
 */


#include "static_polymorphism.hpp"

#include <iostream>


namespace static_polymorphism
{
    void derived::doWorkImpl()
    {
        std::cout << "Implement the base<T>::doWork() in the derived class." << std::endl;
    }

    void concrete_worker::doWork()
    {
        std::cout << "Implement the concrete_worker::doWork()" << std::endl;
    }
}