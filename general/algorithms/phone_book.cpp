/*!
 *  \file       phone_book.cpp
 *  \brief
 *
 */


#include "phone_book.hpp"

bool operator<(const Entry& a, const Entry& b)
{
    return a.number < b.number;
}

std::ostream& operator<<(std::ostream& out_stream, const Entry& entry)
{
    return out_stream << "{\"" << entry.name << "\", " << entry.number << "}";
}

bool operator==(const Entry& a, const Entry& b)
{
    return (a.name == b.name) && (a.number == b.number);
}
