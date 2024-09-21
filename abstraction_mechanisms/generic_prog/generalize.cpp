/*!
 *  \file       generalize.cpp
 *  \brief      
 *  
 */


#include "generalize.hpp"


double add_all(double* array, int n)
{
    double sum{0.0};
    for (int index = 0; index < n; ++index)
    {
        sum += array[index];
    }
    return sum;
}
