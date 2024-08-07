/*!
 *  \file       Dog.cpp
 *  \brief
 *
 */


#include "Dog.hpp"


Dog::Dog(const std::string& name) : Animal(name)
{
}

std::string Dog::name_impl() const
{
    return "I'm " + m_name + " the dog!";
}