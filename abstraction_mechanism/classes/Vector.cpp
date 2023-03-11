/*!
 *  \file   Vector.cpp
 *  \brief  Implement the container class: Vector
 *  
 */


#include "Vector.hpp"

#include <algorithm>

Vector::Vector(std::initializer_list<double> lst) : elem{new double[lst.size()]}, sz{lst.size()}
{
    std::copy(lst.begin(), lst.end(), elem);    /* 从lst拷贝内容到elem中 */
}

double& Vector::operator[](int i)
{
    if ((i < 0) || (i >= size()))
    {
        throw std::out_of_range("Vector::operator[]");
    }
    return elem[i];
}

int Vector::size() const
{
    return sz;
}