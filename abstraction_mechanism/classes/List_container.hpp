/*!
 *  \file   List_container.hpp
 *  \brief  Define a container of List.
 *  
 */


#pragma once

#include "Container.hpp"

#include <list>
#include <initializer_list>

class List_container : public Container
{
private:
    std::list<double> ld;
public:
    List_container();
    List_container(std::initializer_list<double> il);
    ~List_container();

    double& operator[](int i);
    int size() const;
};