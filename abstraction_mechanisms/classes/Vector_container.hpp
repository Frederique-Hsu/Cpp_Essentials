/*!
 *  \file   Vector_container.hpp
 *  \brief  Define and implement a concrete container class: Vector_container
 *  
 */

#pragma once

#include "Container.hpp"
#include "Vector.hpp"

class Vector_container : public Container
{
    Vector v;
public:
    Vector_container(int s);
    Vector_container(std::initializer_list<double>);
    ~Vector_container();

    double& operator[](int i);
    int size() const;
};