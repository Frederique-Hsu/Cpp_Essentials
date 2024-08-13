/*!
 *  \file       leaky_implementation.cpp
 *  \brief
 *
 */


#include "leaky_implementation.hpp"

int do_some_work()
{
    // allocate an array
    double* array = new double[1000];

    // do something

    // forget to deallocate it
    delete[] array;
    return 0;
}