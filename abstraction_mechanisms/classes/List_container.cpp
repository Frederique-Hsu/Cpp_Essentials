/*!
 *  \file   List_container.cpp
 *  \brief  Implement the container of List
 *  
 */


#include "List_container.hpp"

#include <stdexcept>

List_container::List_container()
{
}

List_container::List_container(std::initializer_list<double> il) : ld(il)
{
}

List_container::~List_container()
{
}

double& List_container::operator[](int i)
{
    for (auto& x : ld)
    {
        if (i == 0)
        {
            return x;
        }
        --i;
    }
    throw std::out_of_range("List container");
}

int List_container::size() const
{
    return ld.size();
}