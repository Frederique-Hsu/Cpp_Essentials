/*!
 *  \file       phone_book.hpp
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


bool operator==(const Entry& a, const Entry& b);
std::ostream& operator<<(std::ostream& out_stream, const Entry& entry);
std::istream& operator>>(std::istream& in_stream, Entry& entry);

bool operator<(const Entry& a, const Entry& b);
