/*!
 *  \file       Cat.cpp
 *  \brief
 *
 */


#include "Cat.hpp"


Cat::Cat(const std::string& name) : Animal(name)
{
}

std::string Cat::name_impl() const
{
    return "I'm " + m_name + " the cat!";
}