/*!
 *  \file   Vector.cpp
 *  \brief  Implement the container class: Vector
 *  
 */


#include "Vector.hpp"

double& Vector::operator[](int i)
{
    return elem[i];
}

int Vector::size() const
{
    return sz;
}