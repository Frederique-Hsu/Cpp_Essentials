/*!
 *  \file       String.cpp
 *  \brief
 *
 */


#include "String.hpp"

std::string compose(const std::string& name, const std::string& domain)
{
    return name + '@' + domain;
}
