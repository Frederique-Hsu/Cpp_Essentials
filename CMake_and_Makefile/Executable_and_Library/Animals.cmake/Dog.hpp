/*!
 *  \file       Dog.hpp
 *  \brief
 *
 */


#pragma once


#include "Animal.hpp"

class Dog final : public Animal
{
public:
    Dog(const std::string& name);

private:
    std::string name_impl() const override;
};
