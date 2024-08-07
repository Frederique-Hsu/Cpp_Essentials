/*!
 *  \file       Animal.hpp
 *  \brief
 *
 */


#pragma once


#include <string>

class Animal
{
public:
    Animal() = delete;
    explicit Animal(const std::string& str);
    virtual ~Animal() = default;

protected:
    std::string m_name;

private:
    virtual std::string name_impl() const = 0;

public:
    std::string name() const;
};
