/*!
 *  \file       user_defined_IO.cpp
 *  \brief
 *
 */


#include "user_defined_IO.hpp"

std::ostream& operator<<(std::ostream& out, const Entry& entry)
{
    return out << "{\"" << entry.name << "\", " << entry.number << "}";
}


