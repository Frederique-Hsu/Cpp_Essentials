/*!
 *  \file       user_defined_IO.hpp
 *  \brief
 *
 */


#pragma once

#include <string>
#include <iostream>

struct Entry
{
    std::string name;
    int number;
};


std::ostream& operator<<(std::ostream& out, const Entry& entry);
std::istream& operator>>(std::istream& in, Entry& entry);
