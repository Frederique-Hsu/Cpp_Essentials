/*!
 *  \file       Animal.cpp
 *  \brief
 *
 */


#include "Animal.hpp"

Animal::Animal(const std::string& str) : m_name{str}
{
}

std::string Animal::name() const
{
    return name_impl();
}